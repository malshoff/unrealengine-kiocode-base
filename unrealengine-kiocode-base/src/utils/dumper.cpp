#include "dumper.h"

namespace Dumper {

    void DumpUObjects(SDK::UEngine* Engine)
    {
        std::cout << "***DUMPING OBJECTS***" << std::endl;
        std::cout << Engine->ConsoleClass->GetFullName() << std::endl;

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
    }

    void DumpUActors(SDK::UEngine* Engine, SDK::UWorld* World)
    {
        std::cout << "***DUMPING ACTORS***" << std::endl;

        if (World->Levels.Num() == 0)
            return;

        SDK::ULevel* currLevel = World->Levels[0];
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
    }
}