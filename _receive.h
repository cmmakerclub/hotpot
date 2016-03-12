PubSubClient::callback_t on_message_arrived = [&](const MQTT::Publish & pub) -> void {
  String topic = pub.topic();
  String payload = pub.payload_string();

  if (topic.lastIndexOf("/command") != -1) {
    Serial.println(payload);
    if (payload == "h") {
      digitalWrite(RELAY_02_REBOIL_PIN, LOW);
      delay(250);
      digitalWrite(RELAY_02_REBOIL_PIN, HIGH);
    }
  }
};
