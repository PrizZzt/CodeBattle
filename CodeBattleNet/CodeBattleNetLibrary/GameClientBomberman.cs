using System;

namespace CodeBattleNetLibrary
{
	public class GameClientBomberman : GameClient<BombermanBlocks>
	{
		public GameClientBomberman(string path) : base(path)
		{
		}

		protected override bool IsPlayerCoords(BombermanBlocks block) => block == BombermanBlocks.Bomberman ||
		                                                                 block == BombermanBlocks.BombBomberman ||
		                                                                 block == BombermanBlocks.DeadBomberman;

		protected override BombermanBlocks CharToBlock(char c) =>
			Enum.IsDefined(typeof (BombermanBlocks), (int) c)
				? (BombermanBlocks) c
				: BombermanBlocks.Unknown;
	}
}
