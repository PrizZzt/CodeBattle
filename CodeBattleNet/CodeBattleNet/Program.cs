using System;
using CodeBattleNetLibrary;

namespace CodeBattleNet
{
	internal static class Program
	{
		private static void Main()
		{
			var r = new Random();
			var gcb = new GameClient("localhost:8080", "a@b.ru", "123");
			gcb.Run(() =>
			{
				var done = false;

				switch (r.Next(5))
				{
					case 0:
						if (IsBlock(gcb.Map[gcb.PlayerX, gcb.PlayerY - 1]) == false)
						{
							gcb.Up();
							done = true;
						}
						break;
					case 1:
						if (IsBlock(gcb.Map[gcb.PlayerX + 1, gcb.PlayerY]) == false)
						{
							gcb.Right();
							done = true;
						}
						break;
					case 2:
						if (IsBlock(gcb.Map[gcb.PlayerX, gcb.PlayerY + 1]) == false)
						{
							gcb.Down();
							done = true;
						}
						break;
					case 3:
						if (IsBlock(gcb.Map[gcb.PlayerX - 1, gcb.PlayerY]) == false)
						{
							gcb.Left();
							done = true;
						}
						break;
					case 4:
						gcb.Act();
						done = true;
						break;
				}
				if (done == false)
					gcb.Blank();
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
