import smtplib

server=smtplib.SMTP('smtp.gmail.com',587)
server.starttls()

server.login('senderemail@gmail.com','sender password')

server.sendmail('sender email','reciver email','mail content')
print("mail sent ")