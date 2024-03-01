use serde::{Deserialize, Serialize};
use crate::env;

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Message {
    pub role: String,
    pub content: String,
}

#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct APIMessage {
    pub author: String,
    pub content: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Chat {
    pub channel_id: String,
    pub messages: Vec<Message>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct OpenAIRequest {
    pub channel_id: String,
    pub message: APIMessage,
}

impl Chat {
    pub fn get_or_create(channel_id: &str) -> Chat {
        let prompt = env::var("PROMPT").unwrap_or_default();
        let mut messages = Vec::new();
        if !prompt.is_empty() {
            messages.push(Message {
                role: "system".to_string(),
                content: prompt,
            });
        }
        Chat {
            channel_id: channel_id.to_string(),
            messages,
        }
    }
}
