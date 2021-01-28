#Mengimpor Library Twilio
from twilio.rest import Client
#Mengimpor library dan setup data port serta baudrate import serial
ser = serial.Serial('COM3', 115200)
#Setup Server Twilio
account_sid = 'AC38d1625f74f71508a97e0d2c1721765f' auth_token = '229d3fa575ab68af891d06693deb87ae' client = Client(account_sid, auth_token)

#Perintah untuk membaca data dari serial monitor, mendecode perbaris, lalu mengirimkan data tersebut ke nomor WhatsApp yang dituju

while True:
    while ser.inWaiting():
    temp = ser.readline().decode()
    messageTosend="Danger! The temp is over 95 F! \n Temperature = " + str(temp) + "F" + "Solenoid Valve has been closed."
    message = client.messages.create(body=messageTosend,
                from_='whatsapp:+14155238886',
                to='whatsapp:+6281280261056')

    
print(message.sid)