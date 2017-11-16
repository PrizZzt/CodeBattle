import websocket
import threading
import time
import math
from enum import Enum

class Blocks(Enum):
    Space = ' '

    Brick = '#'
    PitFill1 = '1'
    PitFill2 = '2'
    PitFill3 = '3'
    PitFill4 = '4'
    UndestroyableWall = '☼'

    DrillPit = '*'

    EnemyLadder = 'Q'
    EnemyLeft = '«'
    EnemyRight = '»'
    EnemyPipeLeft = '<'
    EnemyPipeRight = '>'
    EnemyPit = 'X'

    Gold = '$'

    HeroDie = 'Ѡ'
    HeroDrillLeft = 'Я'
    HeroDrillRight = 'R'
    HeroLadder = 'Y'
    HeroLeft = '◄'
    HeroRight = '►'
    HeroFallLeft = ']'
    HeroFallRight = '['
    HeroPipeLeft = '{'
    HeroPipeRight = '}'

    OtherHeroDie = 'Z'
    OtherHeroLeft = ')'
    OtherHeroRight = '('
    OtherHeroLadder = 'U'
    OtherHeroPipeLeft = 'Э'
    OtherHeroPipeRight = 'Є'

    Ladder = 'H'
    Pipe = '~'
    
class ActionTime(Enum):
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
                self.map[j][i] = Blocks.Space
                for k in Blocks:
                    if message[c] == k.value[0]:
                        self.map[j][i] = k
                        if k in [Blocks.HeroDie, Blocks.HeroDrillLeft, Blocks.HeroDrillRight, Blocks.HeroLadder, Blocks.HeroLeft, Blocks.HeroRight, Blocks.HeroFallLeft, Blocks.HeroFallRight, Blocks.HeroPipeLeft, Blocks.HeroPipeRight]:
                            self.playerX = i
                            self.playerY = j
                c = c + 1

        self.on_turn(self)

    def on_error(self, ws, error):
        print(error)

    def on_close(self, ws):
        print("### closed ###")

    def up(self, action = ActionTime.Turn):
        self.socket.send("{}UP{}".format("ACT," if action == ActionTime.BeforeTurn else "",",ACT" if action == ActionTime.AfterTurn else ""))
        
    def down(self, action = ActionTime.Turn):
        self.socket.send("{}DOWN{}".format("ACT," if action == ActionTime.BeforeTurn else "",",ACT" if action == ActionTime.AfterTurn else ""))
        
    def right(self, action = ActionTime.Turn):
        self.socket.send("{}RIGHT{}".format("ACT," if action == ActionTime.BeforeTurn else "",",ACT" if action == ActionTime.AfterTurn else ""))
        
    def left(self, action = ActionTime.Turn):
        self.socket.send("{}LEFT{}".format("ACT," if action == ActionTime.BeforeTurn else "",",ACT" if action == ActionTime.AfterTurn else ""))
        
    def act(self):
        self.socket.send("ACT")
        
    def blank(self):
        self.socket.send("")