import time
import os
import speech_recognition as sr
from gtts import gTTS

from playsound import playsound

def speak(text):
    tts = gTTS(text=text, lang='en')
    tts.save("response.mp3")
    playsound("response.mp3")


def bot_response(input_text):
    if "hello" in input_text:
        response = "Hello! How can I assist you today?"
    elif "makerspace" or "maker space" in input_text:
        response = "The Makerspace is a creative space for hardware enthusiasts."
    elif "projects" in input_text:
        response = "We have many exciting projects going on! What are you interested in?"
    elif "3D printing" in input_text:
        response = "3D printing is a popular project here. Would you like more information?"
    elif "Raspberry Pi" in input_text:
        response = "Raspberry Pi is a versatile single-board computer used in various projects."
    elif "goodbye" in input_text:
        response = "Goodbye! If you have any more questions, feel free to ask."
        exit()
    else:
        response = "I'm sorry, I didn't understand. How can I help you?"

    return response

def get_audio_input():
    recognizer = sr.Recognizer()

    with sr.Microphone() as source:
        print("Listening...")
        audio = recognizer.listen(source)

    try:
        user_input = recognizer.recognize_google(audio)
        return user_input
    except sr.UnknownValueError:
        return ""
    except sr.RequestError:
        print("Could not request results. Please check your internet connection.")
        return ""

while True:
    user_input = get_audio_input()

    if user_input:
        print("You:", user_input)
        response = bot_response(user_input)
        print("B-Bot:", response)
        speak(response)