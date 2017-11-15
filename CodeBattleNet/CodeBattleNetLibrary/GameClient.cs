using System;
using WebSocket4Net;

namespace CodeBattleNetLibrary
{
	public class GameClient
	{
		private readonly WebSocket _socket;
		private event Action OnUpdate;

		public Blocks[,] Map { get; private set; }
		public int MapSize { get; private set; }
		public int PlayerX { get; private set; }
		public int PlayerY { get; private set; }

		public GameClient(string server, string userEmail, string userPassword = null)
		{
			MapSize = 0;

			_socket =
				new WebSocket(
					$"ws://{server}/codenjoy-contest/ws?user={userEmail}{(string.IsNullOrEmpty(userPassword) ? string.Empty : $"&pwd={userPassword}")}");
			_socket.MessageReceived += (s, e) => { ParseField(e.Message); };
		}

		public void Run(Action handler)
		{
			OnUpdate += handler;
			_socket.Open();
		}

		public void Up(ActionTime action = ActionTime.None)
		{
			_socket.Send(
				$"{(action == ActionTime.BeforeTurn ? "ACT," : "")}UP{(action == ActionTime.AfterTurn ? ",ACT" : "")}"
				);
		}

		public void Down(ActionTime action = ActionTime.None)
		{
			_socket.Send(
				$"{(action == ActionTime.BeforeTurn ? "ACT," : "")}DOWN{(action == ActionTime.AfterTurn ? ",ACT" : "")}"
				);
		}

		public void Right(ActionTime action = ActionTime.None)
		{
			_socket.Send(
				$"{(action == ActionTime.BeforeTurn ? "ACT," : "")}RIGHT{(action == ActionTime.AfterTurn ? ",ACT" : "")}"
				);
		}

		public void Left(ActionTime action = ActionTime.None)
		{
			_socket.Send(
				$"{(action == ActionTime.BeforeTurn ? "ACT," : "")}LEFT{(action == ActionTime.AfterTurn ? ",ACT" : "")}"
				);
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
				Map = new Blocks[size, size];
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

		private bool IsPlayerCoords(Blocks block) => block == Blocks.HeroDie ||
		                                             block == Blocks.HeroDrillLeft ||
		                                             block == Blocks.HeroDrillRight ||
		                                             block == Blocks.HeroLadder ||
		                                             block == Blocks.HeroLeft ||
		                                             block == Blocks.HeroRight ||
		                                             block == Blocks.HeroFallLeft ||
		                                             block == Blocks.HeroFallRight ||
		                                             block == Blocks.HeroPipeLeft ||
		                                             block == Blocks.HeroPipeRight;

		private Blocks CharToBlock(char c) =>
			Enum.IsDefined(typeof (Blocks), (int) c)
				? (Blocks) c
				: Blocks.None;
	}
}
