#include "dumper.h"

#include "../config.h"

namespace Dumper {

    void DumpUObjects()
    {
        std::cout << "\n*********************" << std::endl;
        std::cout << "***DUMPING OBJECTS***" << std::endl;

        std::cout << Config::Engine->ConsoleClass->GetFullName() << std::endl;

        for (int i = 0; i < SDK::UObject::GObjects->Num(); i++)
        {
            const SDK::UObject* Obj = SDK::UObject::GObjects->GetByIndex(i);

            if (!Obj)
                continue;

            if (!Obj->IsDefaultObject())
                continue;

            if (Obj->IsA(SDK::APawn::StaticClass()) || Obj->HasTypeFlag(SDK::EClassCastFlags::Pawn))
            {
                std::cout << Obj->GetFullName() << "\n";
            }
        }

        std::cout << "***END DUMPING OBJECTS***" << std::endl;
        std::cout << "*************************\n" << std::endl;
    }

    void DumpUActors()
    {
        std::cout << "\n********************" << std::endl;
        std::cout << "***DUMPING ACTORS***" << std::endl;

        if (Config::World->Levels.Num() == 0)
            return;

        SDK::ULevel* currLevel = Config::World->Levels[0];
        if (!currLevel)
            return;

        for (int j = 0; j < currLevel->Actors.Num(); j++)
        {
            SDK::AActor* currActor = currLevel->Actors[j];

            if (!currActor)
                continue;
            if (!currActor->RootComponent)
                continue;

            std::cout << currActor->GetFullName() << "\n";
        }

        std::cout << "***END DUMPING ACTORS***" << std::endl;
        std::cout << "************************\n" << std::endl;
    }
}