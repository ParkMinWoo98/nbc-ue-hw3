#include "FallingBomb.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "DangerAreaComponent.h"

AFallingBomb::AFallingBomb()
{
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetCollisionProfileName(TEXT("BlockAll"));
	Collision->OnComponentHit.AddDynamic(this, &AFallingBomb::OnHit);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Collision);
	ExplosionCollision->SetVisibility(false);

	DangerArea = CreateDefaultSubobject<UDangerAreaComponent>(TEXT("DangerArea"));
}

void AFallingBomb::BeginPlay()
{
	Super::BeginPlay();

	FVector CurrLocation = GetActorLocation();
	CurrLocation.Z = 4000.0f;
	SetActorLocation(CurrLocation);
	if (DangerArea)
	{
		DangerArea->Spawn(
			FVector(1.0f, 200.0f, 200.0f),
			FVector(CurrLocation.X, CurrLocation.Y, 0.0f),
			FRotator(-90.f, 0.0f, 0.0f),
			2.0f,
			DangerAreaEffectType::FadeIn,
			false);
	}
}

void AFallingBomb::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
	Explode();
}

void AFallingBomb::Explode()
{
	UParticleSystemComponent* Particle = nullptr;
	if (ExplosionParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			ExplosionParticle,
			GetActorLocation(),
			GetActorRotation(),
			false);
		Particle->SetRelativeScale3D(FVector(1.0f, 10.0f, 10.0f));
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			ExplosionSound,
			GetActorLocation());
	}

	TArray<AActor*> OverlappingActors;
	ExplosionCollision->SetVisibility(true);
	ExplosionCollision->SetRelativeLocation(StaticMesh->GetRelativeLocation());
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			UGameplayStatics::ApplyDamage(
				Actor,
				ExplosionDamage,
				nullptr,
				this,
				UDamageType::StaticClass());
		}
	}

	Destroy();

	if (Particle)
	{
		FTimerHandle DestroyParticleTimerHandle;
		TWeakObjectPtr<UParticleSystemComponent> WeakParticle = Particle;

		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			[WeakParticle]()
			{
				if (!WeakParticle.IsValid()) return;
				WeakParticle->DestroyComponent();
			},
			2.0f,
			false);
	}
}