from python_graphql_client import GraphqlClient
import asyncio
import socket

UDP_IP = "192.168.10.113"
UDP_PORT = 52522

def print_handle(data):
    print(str(data["data"]["liveMeasurement"]["power"]))
    MESSAGE = str(data["data"]["liveMeasurement"]["power"]).encode('UTF-8')
    sock = socket.socket(socket.AF_INET, # Internet
                        socket.SOCK_DGRAM) # UDP
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
client = GraphqlClient(endpoint="wss://api.tibber.com/v1-beta/gql/subscriptions")
query = """
subscription{
  liveMeasurement(homeId:"insert_your_home_id_here"){
      power
  }
}
"""
asyncio.run(client.subscribe(query=query, headers={'Authorization': "insert_your_token_here"}, handle=print_handle))

