using System;
using CodeBattleNetLibrary;

namespace CodeBattleNet
{
	internal static class Program
	{
		private static void Main()
		{
			var r = new Random();
			var gc = new GameClient("localhost:8080", "a@b.ru", "123");
			gc.Run(() =>
			{
				var done = false;

				switch (r.Next(5))
				{
					case 0:
						if (IsBlock(gc.Map[gc.PlayerX, gc.PlayerY - 1]) == false)
						{
							gc.Up();
							done = true;
						}
						break;
					case 1:
						if (IsBlock(gc.Map[gc.PlayerX + 1, gc.PlayerY]) == false)
						{
							gc.Right();
							done = true;
						}
						break;
					case 2:
						if (IsBlock(gc.Map[gc.PlayerX, gc.PlayerY + 1]) == false)
						{
							gc.Down();
							done = true;
						}
						break;
					case 3:
						if (IsBlock(gc.Map[gc.PlayerX - 1, gc.PlayerY]) == false)
						{
							gc.Left();
							done = true;
						}
						break;
					case 4:
						gc.Act();
						done = true;
						break;
				}
				if (done == false)
					gc.Blank();
			});

			Console.ReadKey();
		}

		private static bool IsBlock(Blocks block) => block != Blocks.Gold &&
		                                             block != Blocks.None &&
		                                             block != Blocks.Ladder &&
		                                             block != Blocks.Pipe &&
		                                             block != Blocks.PitFill1 &&
		                                             block != Blocks.PitFill2 &&
		                                             block != Blocks.PitFill3 &&
		                                             block != Blocks.PitFill4 &&
		                                             block != Blocks.DrillPit;
	}
}
