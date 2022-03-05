// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FemaleCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTDRAFT_API AFemaleCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFemaleCharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void LookUpAtRate(float Value);

	void ActionPressed();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float baseTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	float baseLookUpAtRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact")
	float traceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isClimbing;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
