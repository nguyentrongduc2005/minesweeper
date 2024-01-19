#include "main.h"
#include "funtion.h"
#include "Console.h"

CauTrucBang Bang;
CauTrucO **CTO;
COORD viTriConTro;
bool suDungPhim = false;
bool TrangThai = false;
short Trang;
short viTriChon = 0;

void taoMang2Chieud()
{
	CTO = new CauTrucO * [Bang.Dong];
	for (int i = 0; i < Bang.Dong; i++)
	{
		CTO[i] = new CauTrucO[Bang.Dong];
	}
}
void xoaMang2Chieud()
{
	for (int i = 0; i < Bang.Dong; i++)
	{
		delete CTO[i];
	}
	delete CTO;	
}
void runing()
{
	
	Menu1(3, 0);
	Trang = 1;
	dieuKienConTro();
	
}

void khoiTao(short Dong, short Cot, short SoBom)
{
	TrangThai = true;
	
	Bang.Dong = Dong;
	Bang.Cot = Cot;
	Bang.SoBom = SoBom;
	Bang.SoCoDaMo = 0;
	Bang.SoODaMo = 0;
	taoMang2Chieud();
	taoBomRanDom();
	veBang();
	dieuKienConTro();

	xoaMang2Chieud();
}




short toaDoX(short SX) // x nhan 2
{
	return (SX * 2) + ((ConsoleWidth/2) - Bang.Cot );
}               
short toaDoY(short SY)// y giu nguyen
{
	return (SY)+((ConsoleHeight/2)-Bang.Dong/2);
}

 void veO(short SX, short SY, short Skieu)
{
	 
	switch (Skieu)
	{
		case 0: // o trong
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 11, "  ");
			break;
		case 1://mau chu trong o 1-8
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 3, 15, "1 ");
			break;
		case 2:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 9,15, "2 ");
			break;
		case 3:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 1, 15, "3 ");
			break;
		case 4:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 3, 15, "4 ");
			break;
		case 5:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 5, 15, "5 ");
			break;
		case 6:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 6, 15, "6 ");
			break;
		case 7:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 12, 15, "7 ");
			break;
		case 8:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 4, 15, "8 ");
			break;
		case 9:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 4, "* "); //O BOM
			break;
		case 10:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 1, 14, "P ");//O Co
			break;
		case 11:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 4, 14, "P ");// O CAM CO SAI
			break;
		case 12:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 10, 14, "P ");// O CAM CO dÚNG
			break;
		case 13:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 7, "  ");//O TRANG
			break;

		case 14:
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 8, "  ");//O DEN 
			break;
		case 15:
			Tao_mau_o(toaDoX(SX)+1, toaDoY(SY), 0, 12, " ");// CON TRO PHIM
			break;

	}
 }
void veBang()
{
	
	
	for (int i = 0; i < Bang.Dong; i++)
	{
		for (int j = 0; j < Bang.Cot; j++)
		{
			if (CTO[i][j].BCamCo)
			{
				veO(j, i, 10);
			}
			else if(CTO[i][j].SoBomLanCan > 0)
			{
				veO(j, i ,CTO[i][j].SoBomLanCan);
			}
			else if (CTO[i][j].BDaMo)
			{
				veO(j, i, 0);
			}
			else if ((i+j)%2)
			{
				veO(j, i, 14);
			}
			else {
				veO(j, i, 13);
			}
			if (suDungPhim)
			{
				veO(viTriConTro.X, viTriConTro.Y, 15);
			}
		}
	}
	veThongSo();
	veTieuDe();
}

void taoBomRanDom()
{
	short SoBom = Bang.SoBom;
	short SI, SJ;//vi tri boooom
	srand(time(NULL));
	while (SoBom)
	{
		SI = rand() % Bang.Dong;
		SJ = rand() % Bang.Cot;
		if (CTO[SI][SJ].BCoBom)
		{
			continue;
		}
		CTO[SI][SJ].BCoBom = 1;
		SoBom--;
	}
}


void xuLyPhimP(short SX, short SY)
{
	
	
		if (!CTO[SY][SX].BDaMo)
		{
			if (CTO[SY][SX].BCamCo)
			{
				Amthanh(MoO);
				CTO[SY][SX].BCamCo = 0;
				Bang.SoCoDaMo--;
			}
			else
			{
				if (Bang.SoBom != Bang.SoCoDaMo)
				{
					Amthanh(MoO);
					CTO[SY][SX].BCamCo = 1;
					Bang.SoCoDaMo++;
					if (Bang.SoCoDaMo + Bang.SoODaMo == Bang.Cot * Bang.Dong)
					{
						gameWin();
					
					}
				}
			}
		}
		if (TrangThai)
		{
			veBang();
		}
	
}
short demBomlanCan(short SX, short SY)
{
	short dem=0;
	for (int i = SY - 1; i <= SY + 1; i++)
	{
		for (int j = SX - 1; j <= SX + 1; j++)
		{
			if (i<0 || i>=Bang.Dong || j<0 || j>=Bang.Cot || (i == SY && j == SX))
			{
				continue;
			}
			else if (CTO[i][j].BCoBom)
			{
				dem++;
			}
			else {
				continue;
			}
		}
	}
	return dem;
}

void Open(short SX, short SY)
{
	if (!CTO[SY][SX].BDaMo && !CTO[SY][SX].BCamCo)
	{
		CTO[SY][SX].BDaMo = 1;
		if (CTO[SY][SX].BCoBom)
		{
			gameOver();
		}
		else
		{
			Bang.SoODaMo++;
			
				short Bom = demBomlanCan(SX, SY);
				if (Bom)// co bom lan can
				{
					CTO[SY][SX].SoBomLanCan = Bom;
				}
				else//kh co bom lam can
				{
					for (int i = SY - 1; i <= SY + 1; i++)
					{
						for (int j = SX - 1; j <= SX + 1; j++)
						{
							if (i < 0 || i >= Bang.Dong || j < 0 || j >= Bang.Cot || (i == SY && j == SX))
							{
								continue;
							}
							Open(j, i);
						}
					}
				}

			
		}
		
	}
	
	
		if (Bang.SoCoDaMo + Bang.SoODaMo == Bang.Cot * Bang.Dong)
		{
			gameWin();
			
		}
	
}

void xuLyPhimO(short SX, short SY)
{
	
	if (!CTO[SY][SX].BDaMo && !CTO[SY][SX].BCamCo)
	{
		Open(SX,SY);
		if (TrangThai)
			veBang();
	}
}
void gameOver()
{
	Amthanh(BomNo);
	Trang = 4;
	TrangThai = false;
	veBang();
	for (int i = 0; i < Bang.Dong; i++)
	{
		for (int j = 0; j < Bang.Cot; j++)
		{
			if (CTO[i][j].BCoBom)
			{
				
					veO(j, i, 9);
				
			}
		}
		
	
	}
	
	for (int i = 0; i < Bang.Dong; i++)
	{
		for (int j = 0; j < Bang.Cot; j++)
		{
			if (CTO[i][j].BCamCo)
			{

				if (CTO[i][j].BCoBom)
				{
					veO(j, i, 12);
				}
				else
				{
					veO(j, i, 11);
				}


			}
		}
	}

	deleteRow(1, 1);
	Tao_mau_o((ConsoleWidth / 2) - 5, 1, 4, 0, "GAME  OVER");
	Menu4(2, 0);
	
	
	
}
void gameWin()
{
	
	Amthanh(Win);
	Trang = 4;
	TrangThai = false;
	veBang();
	for (int i = 0; i < Bang.Dong; i++)
	{
		for (int j = 0; j < Bang.Cot; j++)
		{
			if (CTO[i][j].BCamCo)
			{

				if (CTO[i][j].BCoBom)
				{
					veO(j, i, 12);
				}
				else
				{
					veO(j, i, 11);
				}


			}
		}
	}
	
	
	deleteRow(1, 1);
	Tao_mau_o((ConsoleWidth / 2) - 4, 1, 6, 0, "GAME  WIN");
	Menu4(2, 0);

}

void veTieuDe()
{
	
	
	for (int i = 0; i < ConsoleWidth; i++)
	{
		Tao_mau_o(i, 0, 5, 0,"=");
		Tao_mau_o(i, 3, 5,0, "=");
	}
	Tao_mau_o((ConsoleWidth / 2) - 8, 1, 4, 0, "~ MINESWEEPER ~");
}
void veThongSo()
{
	Sleep(10);
	setBackgroundColor(0);
	gotoXY(8, 7);
	cout << "          ";
	gotoXY(8, 6);
	setBackgroundColor(0);
	setColor(6);
	cout << Bang.SoBom;
	gotoXY(8, 7);
	cout << Bang.SoCoDaMo;
	gotoXY(0, 7);
	cout << "SO CO: ";
	gotoXY(0, 6);
	cout << "SO BOM: ";
	gotoXY(ConsoleWidth-7, 6);
	cout << Bang.Dong << " * " << Bang.Cot;
	gotoXY(ConsoleWidth - 12, 6);
	cout << "MAP: ";
}
void Menu1(short muc,short vitrichon)
{
	veTieuDe();
	if (viTriChon==0)
	{
		Tao_mau_o((ConsoleWidth / 2)-4, 7, 15, 1, " START ");
	}
	else
	{
		Tao_mau_o((ConsoleWidth / 2)-4, 7, 15, 0, " START ");
	}
	if (viTriChon == 1)
	{
		Tao_mau_o((ConsoleWidth / 2)-6, 8, 15, 1, " THONG TIN ");
	}
	else
	{
		Tao_mau_o((ConsoleWidth / 2)-6, 8, 15, 0, " THONG TIN ");
	}
	if (viTriChon == 2)
	{
		Tao_mau_o((ConsoleWidth / 2) - 4, 9, 15, 1, "  EXIT  ");
	}
	else
	{
		Tao_mau_o((ConsoleWidth / 2) - 4, 9, 15, 0, "  EXIT  ");
	}
}
void Menu2(short muc, short vitrichon)
{
	veTieuDe();
	if (viTriChon == 0)
	{
		Tao_mau_o((ConsoleWidth / 2) - 9, 7, 15, 1, "  EASY (9 x 9)  ");
	}
	else
	{
		Tao_mau_o((ConsoleWidth / 2) - 9, 7, 15, 0, "  EASY (9 x 9)  ");
	}
	if (viTriChon == 1)
	{
		Tao_mau_o((ConsoleWidth / 2) - 10, 8, 15, 1, "  HARD (16 x 16)  ");
	}
	else
	{
		Tao_mau_o((ConsoleWidth / 2) - 10, 8, 15, 0, "  HARD (16 x 16)  ");
	}
	if (viTriChon == 2)
	{
		Tao_mau_o((ConsoleWidth / 2) -12, 9, 15, 1, " SUPPER HARD (24 x 24) ");
	}
	else
	{
		Tao_mau_o((ConsoleWidth / 2) -12, 9, 15, 0, " SUPPER HARD (24 x 24) ");
	}

}	
void Menu4(short muc, short vitrichon)
{
	
		if (viTriChon == 0)
		{
			Tao_mau_o(15, 1, 15, 1, " MEW GAME ");
		}
		else
		{
			Tao_mau_o(15, 1, 15, 0, " NEW GAME ");
		}
		if (viTriChon == 1)
		{
			Tao_mau_o(ConsoleWidth  - 15, 1, 15, 1, " EXIT ");
		}
		else
		{
			Tao_mau_o(ConsoleWidth - 15, 1, 15, 0, " EXIT ");
		}
	

}


void dieuKienConTro()
{
	Sleep(10);
	char key_press;
	int ascii_value;

	while (1)
	{
		
		if (_kbhit())

		{
			key_press = _getch();
			ascii_value = key_press;

			switch (ascii_value)
			{
			case 119://w
				
				if (TrangThai) {
					Amthanh(click);
					suDungPhim = true;
					viTriConTro.Y = ((viTriConTro.Y == 0) ? Bang.Dong - 1 : viTriConTro.Y - 1);
					veBang();
					break;
				}
				else
				{
					if (Trang == 1)
					{
						Amthanh(click);
						viTriChon = (viTriChon == 0) ? 2 : viTriChon - 1;
						Menu1(3, viTriChon);
						break;
					}
					if (Trang == 2)
					{
						Amthanh(click);
						viTriChon = (viTriChon == 0) ? 2 : viTriChon - 1;
						Menu2(3, viTriChon);
						break;

					}

				}
			case 115://s
				
				if (TrangThai) {
					Amthanh(click);
					suDungPhim = true;
					viTriConTro.Y = ((viTriConTro.Y == Bang.Dong - 1) ? 0 : viTriConTro.Y + 1);
					veBang();
					break;
				}
				else
				{
					if (Trang == 1)
					{
						Amthanh(click);
						viTriChon = (viTriChon == 2) ? 0 : viTriChon + 1;
						Menu1(3, viTriChon);
						break;
					}
					if (Trang == 2)
					{
						Amthanh(click);
						viTriChon = (viTriChon == 2) ? 0 : viTriChon + 1;
						Menu2(3, viTriChon);
						break;

					}

				}
			case 97://a
			
				if (TrangThai) {
					Amthanh(click);
					suDungPhim = true;
					viTriConTro.X = ((viTriConTro.X == 0) ? Bang.Cot - 1 : viTriConTro.X - 1);
					veBang();
					break;
				}
				else
				{
					if (Trang == 4) {
						Amthanh(click);
						viTriChon = (viTriChon == 0) ? 1 : viTriChon - 1;
						Menu4(2, viTriChon);
						break;


					}
					else {
						break;
					}
				}
			case 100://d
				if (TrangThai) {
					Amthanh(click);
					suDungPhim = true;
					viTriConTro.X = ((viTriConTro.X == Bang.Cot - 1) ? 0 : viTriConTro.X + 1);
					veBang();
					break;
				}
				else
				{
					if (Trang == 4) {
						Amthanh(click);
						viTriChon = (viTriChon == 1) ? 0 : viTriChon + 1;
						Menu4(2, viTriChon);
						break;


					}
					else {
						break;
					}
				}
			case 112://p
				if (TrangThai) {
					xuLyPhimP(viTriConTro.X, viTriConTro.Y);
					break;
				}
				else {
					break;
				}
			case 111://o
				if (TrangThai) {
					Amthanh(MoO);
					xuLyPhimO(viTriConTro.X, viTriConTro.Y);
					break;
				}
				else {
					break;
				}
			case 13://enter
				if (Trang == 1)
				{
					Amthanh(click);
					//so trang 1
					if (viTriChon == 0)
					{
						viTriChon = 0;
						Trang = 2;
						deleteRow(7, 3);
						Menu2(3, viTriChon);
						break;
					}
					if (viTriChon == 1)
					{
						break;
					}
					if (viTriChon == 2)
					{
						xoaMang2Chieud();
						exit(0);
						break;
					}

				}
				if (Trang == 2)
				{
					Amthanh(click);
					//so trang 2
					if (viTriChon == 0)
					{
						Trang = 3;
						viTriConTro.X = 0;
						viTriConTro.Y = 0;
						deleteRow(0, 24);
						khoiTao(9, 9, 10);
						break;
					}
					if (viTriChon == 1)
					{
						Trang = 3;
						deleteRow(0, 30);
						gotoXY(0, 0);
						khoiTao(16, 16, 35);
						break;
					}
					if (viTriChon == 2)
					{
						Trang = 3;

						khoiTao(24, 24, 99);
						break;
					}
				}
				if (Trang == 4)
				{
					Amthanh(click);
					if (viTriChon == 0)
					{
						viTriChon = 0;
						Trang = 2;
						deleteRow(0, 30);
						Menu2(3, viTriChon);
						break;
					}
					if (viTriChon == 1)
					{
						xoaMang2Chieud();
						exit(0);
					}
				}
				break;

			case 27://ESc
				
				switch (Trang)
				{
				case 1://so trang 1
					exit(0);

				case 2://so trang 2
					viTriChon = 0;
					Trang = 1;
					deleteRow(0, 30);
					Menu1(3, viTriChon);
					break;
				case 3://dg choi
					TrangThai = false;
					viTriChon = 0;
					Trang = 2;
					deleteRow(0, 30);
					Menu2(3, viTriChon);

					break;
				case 4://so trang 4
					xoaMang2Chieud();
					exit(0);
					break;


				}

			}
		}
	}
}