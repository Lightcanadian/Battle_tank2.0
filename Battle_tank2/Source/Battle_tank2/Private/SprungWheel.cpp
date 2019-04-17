// Copyright embraced IT limited

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	
	SetRootComponent(Spring);

	/*Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetSimulatePhysics(true);
	Mass->SetupAttachment(RootComponent);*/

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetSimulatePhysics(true);
	//***New way to attach to root, can only be done in constructor***//
	Wheel->SetupAttachment(RootComponent);

	//Wheel->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);	

	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	//Attach the tank body as the main constraint body
	SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* Body = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!Body) return;
	Spring->SetConstrainedComponents(Body, NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
}

