#pragma once
class Dummy
{
public:
	// *******************************************
	// gifts:
	
	// 1 - constructor par défaut (disparait si au moins 1 déclaré)
	// 2 - constructor par copy + operator de copy
	// 3 - constructor par move + operator de move
	// 4 - destructeur par défaut (pas virtual)

	// ***********************************************
	// remove gift
	
	// default:
	// Dummy() = delete;

	// copy
	//Dummy() = default;
	//Dummy(const Dummy& dummy) = delete;
	//Dummy& operator=(const Dummy& dummy) = delete;

	// move
	//Dummy() = default;
	//Dummy(const Dummy& dummy) = default;
	//Dummy& operator=(const Dummy& dummy) = default;
	//Dummy(Dummy&& dummy) = delete;
	//Dummy&& operator=(Dummy&& dummy) = delete;

};

