using System;
using WebSocket4Net;

namespace CodeBattleNetLibrary
{
	public abstract class GameClient<TBlocks>
	{
		private readonly WebSocket _socket;
		public event Action OnUpdate;

		public TBlocks[,] Map { get; private set; }
		public int MapSize { get; private set; }
		public int PlayerX { get; private set; }
		public int PlayerY { get; private set; }

		protected GameClient(string path)
		{
			MapSize = 0;

			_socket = new WebSocket(path);
			_socket.MessageReceived += (s, e) => { ParseField(e.Message); };
			_socket.Open();
		}

		public void Up()
		{
			_socket.Send("UP");
		}

		public void Down()
		{
			_socket.Send("DOWN");
		}

		public void Right()
		{
			_socket.Send("RIGHT");
		}

		public void Left()
		{
			_socket.Send("LEFT");
		}

		public void Act()
		{
			_socket.Send("ACT");
		}

		public void Blank()
		{
			_socket.Send("");
		}

		private void ParseField(string rawField)
		{
			rawField = rawField.Substring(6);
			int size = (int) Math.Sqrt(rawField.Length);
			if (MapSize != size)
			{
				Map = new TBlocks[size, size];
				MapSize = size;
			}

			int rawPosition = 0;
			for (int j = 0; j < size; j++)
			{
				for (int i = 0; i < size; i++)
				{
					Map[i, j] = CharToBlock(rawField[rawPosition]);

					if (IsPlayerCoords(Map[i, j]))
					{
						PlayerX = i;
						PlayerY = j;
					}

					rawPosition++;
				}
			}

			OnUpdate?.Invoke();
		}
		
		protected abstract bool IsPlayerCoords(TBlocks block);
		protected abstract TBlocks CharToBlock(char c);
	}
}
