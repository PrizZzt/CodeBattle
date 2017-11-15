import websocket
import threading
import time
import math
from enum import Enum

class BombermanBlocks(Enum):
    Unknown = 0,

    Bomberman = u'☺',
    BombBomberman = u'☻',
    DeadBomberman = u'Ѡ',

    OtherBomberman = u'♥',
    OtherBombBomberman = u'♠',
    OtherDeadBomberman = u'♣',

    BombTimer5 = u'5',
    BombTimer4 = u'4',
    BombTimer3 = u'3',
    BombTimer2 = u'2',
    BombTimer1 = u'1',
    Boom = u'҉',

    Wall = u'☼',
    WallDestroyable = u'#',
    DestroyedWall = u'H',

    MeatChopper = u'&',
    DeadMeatChopper = u'x',

    Space = u' '
    
class BombAction(Enum):
		Turn = 0,
		BeforeTurn = 1,
		AfterTurn = 2

class GameClient:
    def __init__(self, server, userEmail, userPassword = None):
        path = "ws://" + server + "/codenjoy-contest/ws?user=" + userEmail + (("&pwd=" + userPassword) if userPassword != None else "")
        self.socket = websocket.WebSocketApp(path, on_message = self.on_message, on_error = self.on_error, on_close = self.on_close)
    
    def run(self, on_turn = None):
        self.on_turn = on_turn
        self.socket.run_forever()

    def on_message(self, ws, message):
        self.mapSize = math.ceil(math.sqrt(len(message) - 6))
        
        self.map = [[0 for x in range(self.mapSize)] for y in range(self.mapSize)] 
        c = 6
        for j in range(self.mapSize):
            for i in range(self.mapSize):
                self.map[j][i] = BombermanBlocks.Unknown
                for k in BombermanBlocks:
                    if message[c] == k.value[0]:
                        self.map[j][i] = k
                        if k == BombermanBlocks.Bomberman or k == BombermanBlocks.BombBomberman or k == BombermanBlocks.DeadBomberman:
                            self.playerX = i
                            self.playerY = j
                c = c + 1

        self.on_turn(self)

    def on_error(self, ws, error):
        print(error)

    def on_close(self, ws):
        print("### closed ###")

    def up(self, action = BombAction.Turn):
        self.socket.send("{}UP{}".format("ACT," if action == BombAction.BeforeTurn else "",",ACT" if action == BombAction.AfterTurn else ""))
        
    def down(self, action = BombAction.Turn):
        self.socket.send("{}DOWN{}".format("ACT," if action == BombAction.BeforeTurn else "",",ACT" if action == BombAction.AfterTurn else ""))
        
    def right(self, action = BombAction.Turn):
        self.socket.send("{}RIGHT{}".format("ACT," if action == BombAction.BeforeTurn else "",",ACT" if action == BombAction.AfterTurn else ""))
        
    def left(self, action = BombAction.Turn):
        self.socket.send("{}LEFT{}".format("ACT," if action == BombAction.BeforeTurn else "",",ACT" if action == BombAction.AfterTurn else ""))
        
    def act(self):
        self.socket.send("ACT")
        
    def blank(self):
        self.socket.send("")