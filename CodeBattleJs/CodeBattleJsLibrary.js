var Blocks =
{
  None: ' ',

  Brick: '#',
  PitFill1: '1',
  PitFill2: '2',
  PitFill3: '3',
  PitFill4: '4',
  UndestroyableWall: '☼',

  DrillPit: '*',

  EnemyLadder: 'Q',
  EnemyLeft: '«',
  EnemyRight: '»',
  EnemyPipeLeft: '<',
  EnemyPipeRight: '>',
  EnemyPit: 'X',

  Gold: '$',

  HeroDie: 'Ѡ',
  HeroDrillLeft: 'Я',
  HeroDrillRight: 'R',
  HeroLadder: 'Y',
  HeroLeft: '◄',
  HeroRight: '►',
  HeroFallLeft: ']',
  HeroFallRight: '[',
  HeroPipeLeft: '{',
  HeroPipeRight: '}',

  OtherHeroDie: 'Z',
  OtherHeroLeft: ')',
  OtherHeroRight: '(',
  OtherHeroLadder: 'U',
  OtherHeroPipeLeft: 'Э',
  OtherHeroPipeRight: 'Є',

  Ladder: 'H',
  Pipe: '~'
};

var ActionTime =
{
  None: 0,
  BeforeTurn: 1,
  AfterTurn: 2
};

class GameClient
{
  constructor(server, userEmail, userPassword = "")
  {
    this.path = "ws://" + server + "/codenjoy-contest/ws?user=" + userEmail + (userPassword == "" ? "" : "&pwd=" + userPassword)
  }
  
  run(callback)
  {
    this.socket = new WebSocket(this.path);
    this.socket.onmessage = function(event)
    {
      var data = event.data.substring(6);
      this.size = Math.sqrt(data.length);
      var currentChar = 0;
      
      this.map = [];
      for(var j = 0; j < this.size; j++)
      {
        this.map[j] = [];
        for(var i = 0; i < this.size; i++)
        {
          for(var key in Blocks)
          {
            if(data[currentChar] == Blocks[key])
            {
              this.map[j][i] = Blocks[key];
              if(
                this.map[j][i] == Blocks.HeroDie ||
                this.map[j][i] == Blocks.HeroDrillLeft ||
                this.map[j][i] == Blocks.HeroDrillRight ||
                this.map[j][i] == Blocks.HeroLadder ||
                this.map[j][i] == Blocks.HeroLeft ||
                this.map[j][i] == Blocks.HeroRight ||
                this.map[j][i] == Blocks.HeroFallLeft ||
                this.map[j][i] == Blocks.HeroFallRight ||
                this.map[j][i] == Blocks.HeroPipeLeft ||
                this.map[j][i] == Blocks.HeroPipeRight
                )
              {
                this.playerX = i;
                this.playerY = j;
              }
            }
          }
          currentChar++;
        }
      }
      
      callback();
    }
  }
  
  get size()    { return this.socket.size;    }
  get map()     { return this.socket.map;     }
  get playerX() { return this.socket.playerX; }
  get playerY() { return this.socket.playerY; }
  
  set onopen(callback)  { this.socket.onopen  = callback; }
  set onclose(callback) { this.socket.onclose = callback; }
  set onerror(callback) { this.socket.onerror = callback; }
  
  up(action = ActionTime.None)
  {
    this.socket.send((action == ActionTime.BeforeTurn ? "ACT,": "") + "UP" + (action == ActionTime.AfterTurn ? ",ACT": ""));
  }
  
  down(action = ActionTime.None)
  {
    this.socket.send((action == ActionTime.BeforeTurn ? "ACT,": "") + "DOWN" + (action == ActionTime.AfterTurn ? ",ACT": ""));
  }
  
  right(action = ActionTime.None)
  {
    this.socket.send((action == ActionTime.BeforeTurn ? "ACT,": "") + "RIGHT" + (action == ActionTime.AfterTurn ? ",ACT": ""));
  }
  
  left(action = ActionTime.None)
  {
    this.socket.send((action == ActionTime.BeforeTurn ? "ACT,": "") + "LEFT" + (action == ActionTime.AfterTurn ? ",ACT": ""));
  }
  
  act() { this.socket.send("ACT"); }
  blank() { this.socket.send(""); }  
}
