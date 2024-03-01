#include "../inc/JsonBuilder.hpp"

std::string JsonBuilder::getCompletionJson(const std::string& nickname, const std::string& channel, const std::string& message) {
    std::ostringstream jsonPayload;
    jsonPayload << "{\"channel_id\": \"" << channel << "\", \"message\": {\"content\": \"" << message << "\", \"author\": \"" << nickname << "\"}}";
    return jsonPayload.str();
}
