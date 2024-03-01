use actix_web::{web, App, HttpServer, HttpResponse, Responder};
use dotenv::dotenv;
use reqwest;
use serde_json::json;
use std::env;
use std::sync::Mutex;
use lazy_static::lazy_static;
use std::collections::HashMap;

mod models;
use models::{Chat, Message, OpenAIRequest};

lazy_static! {
    static ref CHATS: Mutex<HashMap<String, Chat>> = Mutex::new(HashMap::new());
}

async fn chat(data: web::Json<OpenAIRequest>) -> impl Responder {
    // Get conversation history from memory
    let mut chats = CHATS.lock().unwrap();
    let conversation = chats.entry(data.channel_id.clone()).or_insert(Chat::get_or_create(&data.channel_id));

    println!("Processing message from user {} in channel {}", &data.message.author, &data.channel_id);

    // Store user message in conversation history
    let user_message = Message {
        role: String::from("user"),
        content: format!("{}: {}", &data.message.author, &data.message.content),
    };
    conversation.messages.push(user_message.clone());
  
    // Call OpenAI API
    let openai_response = call_openai_api(&conversation.messages).await;

    let openai_response = match serde_json::from_str::<serde_json::Value>(&openai_response) {
        Ok(value) => value["choices"][0]["message"]["content"].as_str().unwrap_or_else(|| "").to_string(),
        Err(_) => String::new(),
    };

    // Store assistant message in conversation history
    let assistant_message = Message {
        role: String::from("assistant"),
        content: openai_response.clone(),
    };
    conversation.messages.push(assistant_message.clone());

    // Return response to the client
    HttpResponse::Ok().json(json!({"response": openai_response}))
}

async fn call_openai_api(data: &Vec<Message>) -> String {
    // Retrieve OpenAI API key from environment variable
    let api_key = env::var("OPENAI_API_KEY").unwrap_or_else(|_| String::new());
    if api_key.is_empty() {
        eprintln!("Error: OpenAI API key is not set.");
        return String::new();
    }

    // Set OpenAI API endpoint URL
    let url = "https://api.openai.com/v1/chat/completions";

    // Prepare data for OpenAI API
    let model = env::var("OPENAI_MODEL").unwrap_or_else(|_| "gpt-3.5-turbo".to_string());
    let openai_request = json!({
        "model": model,
        "messages": data,
    });

    // Make API request
    let client = reqwest::Client::new();
    let response = client.post(url)
        .header("Content-Type", "application/json")
        .header("Authorization", format!("Bearer {}", api_key))
        .body(serde_json::to_string(&openai_request).unwrap())
        .send()
        .await;

    match response {
        Ok(res) => res.text().await.unwrap_or_else(|_| String::new()),
        Err(_) => String::from("Error: OpenAI API request failed."),
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    // Load environment variables from .env file
    dotenv().ok();
    println!("Loaded environment variables from .env file (if present)");

    let port = env::var("PORT").unwrap_or_else(|_| "8080".to_string());
    println!("Starting HTTP server on 0.0.0.0:{}", port);
    HttpServer::new(|| {
        App::new()
            .route("/api/v1/chat", web::post().to(chat))
    })
    .bind(format!("0.0.0.0:{}", port))?
    .run()
    .await
}

