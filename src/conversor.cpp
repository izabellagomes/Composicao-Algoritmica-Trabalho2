#include "conversor.hpp"

Conversor::Conversor()
{

}

int Conversor::chromatic2diatonic(int pitch)
{
	switch(pitch)
	{
		case 60:
			return 1;
			break;
		case 62:
			return 2;
			break;
		case 64:
			return 3;
			break;
		case 65:
			return 4;
			break;
		case 67:
			return 5;
			break;
		case 69:
			return 6;
			break;
		case 71:
			return 7;
			break;
		case 72:
			return 8;
			break;
		case 74:
			return 9;
			break;
		case 76:
			return 10;
			break;
		case 77:
			return 11;
			break;
		case 79:
			return 12;
			break;
		default:
			return -1;

	}
}

int Conversor::diatonic2chromatic(int pitch)
{
	switch(pitch)
	{
		case 1:
			return 60;
			break;
		case 2:
			return 62;
			break;
		case 3:
			return 64;
			break;
		case 4:
			return 65;
			break;
		case 5:
			return 67;
			break;
		case 6:
			return 69;
			break;
		case 7:
			return 71;
			break;
		case 8:
			return 72;
			break;
		case 9:
			return 74;
			break;
		case 10:
			return 76;
			break;
		case 11:
			return 77;
			break;
		case 12:
			return 79;
			break;
		default:
			return -1;

	}
}