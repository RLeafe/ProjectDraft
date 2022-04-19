// Fill out your copyright notice in the Description page of Project Settings.


#include "FemaleCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFemaleCharacterBase::AFemaleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	//Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	baseTurnRate = 45.0f;
	baseLookUpAtRate = 32.0f;
}

void AFemaleCharacterBase::MoveForward(float Value)
{
	if (isClimbing != false) return;

	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AFemaleCharacterBase::MoveRight(float Value)
{
	if (isClimbing != false) return;

	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AFemaleCharacterBase::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * baseTurnRate * GetWorld()->GetDeltaSeconds()); //GetWorld()->GetDeltaSeconds() (framerate)
}

void AFemaleCharacterBase::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * baseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

void AFemaleCharacterBase::ActionPressed()
{
	/*FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	traceDistance = 2000.0;

	GetController()->GetPlayerViewPoint(Loc, Rot);

	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * traceDistance);

	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	DrawDebugLine(GetWorld(), Start, End, FColor::Purple, false, 2.0);*/
}

// Called every frame
void AFemaleCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFemaleCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/// <summary>
	/// ACTION BINDS
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	/*PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);*/

	PlayerInputComponent->BindAction("Action", IE_Released, this, &AFemaleCharacterBase::ActionPressed);

	/// <summary>
	/// AXIS BINDS
	/// </summary>
	/// <param name="PlayerInputComponent"></param>
	PlayerInputComponent->BindAxis("MoveForward", this, &AFemaleCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFemaleCharacterBase::MoveRight);

	//Mouse
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//Controller
	PlayerInputComponent->BindAxis("TurnRate", this, &AFemaleCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFemaleCharacterBase::LookUpAtRate);


}

