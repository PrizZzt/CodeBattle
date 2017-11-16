from CodeBattlePythonLibrary import GameClient
from CodeBattlePythonLibrary import Blocks
import math
import random

def isBlock(block):
    return (block in [
        Blocks.Gold,
		    Blocks.Space,
		    Blocks.Ladder,
		    Blocks.Pipe,
		    Blocks.PitFill1,
		    Blocks.PitFill2,
		    Blocks.PitFill3,
		    Blocks.PitFill4,
		    Blocks.DrillPit] == False)

def turn(gc):
    done = False;
    val = math.ceil(random.random() * 5 - 0.5)
        
    if val == 0:
        if isBlock(gc.map[gc.playerY - 1][gc.playerX]) == False:
            gc.up()
            done = True
    if val == 1:
        if isBlock(gc.map[gc.playerY][gc.playerX + 1]) == False:
            gc.right()
            done = True
    if val == 2:
        if isBlock(gc.map[gc.playerY + 1][gc.playerX]) == False:
            gc.down()
            done = True
    if val == 3:
        if isBlock(gc.map[gc.playerY][gc.playerX - 1]) == False:
            gc.left()
            done = True
    if val == 4:
        gc.act()
        done = True
    if done == False:
        gc.blank();

random.seed()
gc = GameClient("localhost:8080", "a@b.ru", "123")
gc.run(turn)
