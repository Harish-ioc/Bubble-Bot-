import json
import random

def load_json_from_file(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)

def respond_to_user_input(user_input, json_context):
    user_words = user_input.lower().split()

    best_match_key = None
    max_matching_words = 0

    for context_dict in json_context:
        for key, value_list in context_dict.items():
            matching_words = len(set(user_words) & set(key.split()))
            if matching_words > max_matching_words:
                max_matching_words = matching_words
                best_match_key = key

    if best_match_key is not None:
        response_list = next(item[best_match_key] for item in json_context if best_match_key in item)
        return random.choice(response_list)
    else:
        return "I'm sorry, I didn't understand that. Please try again."


file_path = 'data.json'
json_context = load_json_from_file(file_path)

while True:
    user_input = input("You : ")
    
    if user_input=="exit/":
        print("Exiting...")
        break   

    response = respond_to_user_input(user_input, json_context)
    print("Bot : ",response)
