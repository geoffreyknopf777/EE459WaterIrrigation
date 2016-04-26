from __future__ import print_function
import httplib2
import os

from apiclient import discovery
import oauth2client
from oauth2client import client
from oauth2client import tools

import time
import serial
import datetime
from datetime import timedelta

try:
    import argparse
    flags = argparse.ArgumentParser(parents=[tools.argparser]).parse_args()
except ImportError:
    flags = None

# If modifying these scopes, delete your previously saved credentials
# at ~/.credentials/calendar-python-quickstart.json
SCOPES = 'https://www.googleapis.com/auth/calendar.readonly'
CLIENT_SECRET_FILE = 'client_secret.json'
APPLICATION_NAME = 'Google Calendar API Python Quickstart'


def get_credentials():
    """Gets valid user credentials from storage.

    If nothing has been stored, or if the stored credentials are invalid,
    the OAuth2 flow is completed to obtain the new credentials.

    Returns:
        Credentials, the obtained credential.
    """
    home_dir = os.path.expanduser('~')
    credential_dir = os.path.join(home_dir, '.credentials')
    if not os.path.exists(credential_dir):
        os.makedirs(credential_dir)
    credential_path = os.path.join(credential_dir, 'calendar-python-quickstart.json')
    store=oauth2client.file.Storage(credential_path)
    credentials=store.get();
    if not credentials or credentials.invalid:
        flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
        flow.user_agent = APPLICATION_NAME
        if flags:
            credentials = tools.run_flow(flow, store, flags)
        else: # Needed only for compatibility with Python 2.6
            credentials = tools.run(flow, store)
        print('Storing credentials to ' + credential_path)
    return credentials
def main():
    """Shows basic usage of the Google Calendar API.

    Creates a Google Calendar API service object and outputs a list of the next
    10 events on the user's calendar.
    """
    credentials = get_credentials()
    http = credentials.authorize(httplib2.Http())
    service = discovery.build('calendar', 'v3', http=http)

    print('Serial Init')
    port = serial.Serial("/dev/ttyAMA0", baudrate=115200, timeout=3.0)

    while True:

        print('Wait for Schedule Request')
        msg='GetSchedule'
        rcv = port.read(len(msg))
        print('Message received: ', rcv)
        if msg == rcv:
				
          print('Get current time')
          now = datetime.datetime.utcnow().isoformat() + 'Z' # 'Z' indicates UTC time
          later = (datetime.datetime.utcnow() + timedelta(minutes=1)).isoformat() + 'Z'
    
          print('Zone1 Check Schedule')
          eventsResult = service.events().list(
            calendarId='2b7pf2m67omiv970o9adi1rop4@group.calendar.google.com', timeMin=now, timeMax=later, maxResults=1, singleEvents=True,
          orderBy='startTime').execute()
          events = eventsResult.get('items', [])

          if not events:
              print('Zone1 off')
              zone1=0
          for event in events:
              print('Zone1 on')
              zone1=1


          print('Zone2 Check Schedule')
          eventsResult = service.events().list(
            calendarId='dsmibip218ev9ubhp33pnc2pn8@group.calendar.google.com', timeMin=now, timeMax=later, maxResults=1, singleEvents=True,
          orderBy='startTime').execute()
          events = eventsResult.get('items', [])

          if not events:
              print('Zone2 off')
              zone2=0
          for event in events:
              print('Zone2 on')
              zone2=1

          print('Send Control Signals')
          #Zone1
          port.write(repr(zone1))
          #Zone2
          port.write(repr(zone2))
          print('')

if __name__ == '__main__':
    main()
