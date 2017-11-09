from CodeBattlePythonLibrary import GameClient
from CodeBattlePythonLibrary import BombermanBlocks
import math
import random

def isBlock(block):
    return block in [
        BombermanBlocks.Wall,
        BombermanBlocks.WallDestroyable,
        BombermanBlocks.MeatChopper,
        BombermanBlocks.BombTimer1,
        BombermanBlocks.BombTimer2,
        BombermanBlocks.BombTimer3,
        BombermanBlocks.BombTimer4,
        BombermanBlocks.BombTimer5,
        BombermanBlocks.OtherBomberman,
        BombermanBlocks.OtherBombBomberman]

def turn(gcb):
    done = False;
    val = math.ceil(random.random() * 5 - 0.5)
        
    if val == 0:
        if isBlock(gcb.map[gcb.playerY - 1][gcb.playerX]) == False:
            gcb.up()
            done = True
    if val == 1:
        if isBlock(gcb.map[gcb.playerY][gcb.playerX + 1]) == False:
            gcb.right()
            done = True
    if val == 2:
        if isBlock(gcb.map[gcb.playerY + 1][gcb.playerX]) == False:
            gcb.down()
            done = True
    if val == 3:
        if isBlock(gcb.map[gcb.playerY][gcb.playerX - 1]) == False:
            gcb.left()
            done = True
    if val == 4:
        gcb.act()
        done = True
    if done == False:
        gcb.blank();

random.seed()
GameClient("ws://localhost:8080/codenjoy-contest/ws?user=ab@c.ru", turn)
