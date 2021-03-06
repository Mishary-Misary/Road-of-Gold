﻿#include"Urban.h"
#include"Group.h"
#include"Vehicle.h"
#include"Node.h"
#include"Planet.h"
#include"Route.h"
#include"UI.h"
#include"Sound.h"
#include"Scuttle.h"
#include"Data.h"
#include"VehicleData.h"

void Main()
{
	{
		Window::SetTitle(L"Road of Gold");

		INIReader iniReader(L"assets/config.ini");
		if (iniReader.getOr<bool>(L"Window", L"FullScreen", false)) Graphics::SetFullScreen(true, Graphics::EnumOutputs().front().displayModes.back().size);
		else Window::Resize(iniReader.getOr<Size>(L"Window", L"WindowSize", Size(1280, 720)));
	}

	Output << L"WindowSize:", Window::Size();
	Output << L"FullScreen:", Window::GetState().fullScreen;

	//Fontの展開
	Array<Font> fonts;
	{
		size_t size = 1024;
		fonts.reserve(size);
		ui.fonts.reserve(size);
		for (auto i : step(size)) fonts.emplace_back(i);
		for (auto i : step(size)) ui.fonts.emplace_back(&fonts.at(i));
	}

	initSounds();

	if (!selectMap()) return;

	initGroups();

	Output << L"MainLoopの開始";

	auto bgmItems = FileSystem::DirectoryContents(L"assets/BGM/").filter([](const String& s) { return FileSystem::IsFile(s) && FileSystem::Extension(s) == L"mp3"; });

	while (System::Update())
	{
		if (!bgm.isPlaying() && !bgmItems.isEmpty())
		{
			bgm = Audio(bgmItems.choice());
			bgm.play();
		}

		if (KeyB.down())
		{
			for (int i = 0; i < 100; i++) vehicles.emplace_back(vehicleData.choice().id(), &urbans.choice());
		}

		tinyCamera.update();
		updateTimeSpeed();
		updateScuttles();
		selectItem();

		if (planet.timeSpeed > 0)
		{
			updatePlanet();
			updateVehicles();
			updateUrbans();
			updateGroups();
		}

		drawPlanet();
		drawRotues();
		drawVehicles();
		drawUrbans();
		drawGroups();
		drawUI();
		drawScuttles();
	}
}
