use serde::{Deserialize, Serialize};

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
        Chat {
            channel_id: channel_id.to_string(),
            messages: Vec::new(),
        }
    }
}

