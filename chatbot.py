import random
import nltk
from nltk.stem import PorterStemmer
from nltk.tokenize import word_tokenize
from data import data

# Setup NLTK
nltk.download("punkt")
stemmer = PorterStemmer()

# Intent mapping
INTENT_RESPONSE_MAP = {
    "greetings": "responses",
    "workout_advice": "workout_responses",
    "diet": "diet_responses",
    "motivation": "motivation_responses",
    "rest_recovery": "rest_responses",
    "hydration": "hydration_responses",
    "equipment_advice": "equipment_responses",
    "farewells": "farewell_responses"
}

# NLP preprocessing
def preprocess(sentence):
    tokens = word_tokenize(sentence.lower())
    return [stemmer.stem(token) for token in tokens]

# Get response from intent
def get_response(user_input):
    processed_input = set(preprocess(user_input))
    best_match = None
    max_overlap = 0

    for intent_category, response_category in INTENT_RESPONSE_MAP.items():
        for pattern in data[intent_category]:
            processed_pattern = set(preprocess(pattern))
            overlap = len(processed_pattern & processed_input) # count of common words
            # Check if this pattern has more overlap than the current best match
            #us:suggest workout for daily ex
            #bot:suggest workout,suggest diet
            
            if overlap > max_overlap:
                max_overlap = overlap
                best_match = response_category

    if best_match:
        return random.choice(data[best_match])
    
    return ("I'm not sure how to respond to that. "
            "Try asking about workouts, diet, rest, or motivation.")


# Chat loop
def chat():
    print("Chatbot: Hello! I'm your fitness assistant. Type 'exit' to quit.")
    while True:
        user_input = input("You: ").strip()
        if user_input.lower() == "exit":
            print("Chatbot: Stay healthy! Goodbye!")
            break
        response = get_response(user_input)
        print(f"Chatbot: {response}")

# Run the chatbot
if __name__ == "__main__":
    chat()
