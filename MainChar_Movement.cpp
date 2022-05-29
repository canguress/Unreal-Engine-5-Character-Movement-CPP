// Fill out your copyright notice in the Description page of Project Settings.
/*
* 
* @author canguress
* https://github.com/canguress/
* cangures1912@gmail.com
* 

*/

#include "MainChar_Movement.h"

// Sets default values
AMainChar_Movement::AMainChar_Movement()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false; //Controllerýn kamerayý deðil, kameranýn kontroller'ý yöneltmesini saðladým
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	GetCharacterMovement()->bOrientRotationToMovement = true; 
	/*
	* If this is going to be true (which it is) Rotates the character towards the direction of acceleration
	
	*/


	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	/*
	* This makes the rate of rotation change
	*/

	GetCharacterMovement()->JumpZVelocity = 600.f;
	/*
	* When we jump, this velocity is going to our speed.
	*/

	GetCharacterMovement()->AirControl = 0.15f;
	/*
	* AirControl is, how much we are able to control our character while the character is on the air (jumped)
	*/

	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	/*
	* Our root component is a CapsuleComponent in our MainChar_BP (You can see the BP Resource at image attachments in the project.)
	*/

	CameraBoom->TargetArmLength = 100.0f;
	/*
	* How far is going to camera far from the player 
	* I AM DOING THIS FOR FPS (FIRST PERSON SHOOTER) YOU CAN CHANGE THIS ONE AS YOU WISH!!!
	*/

	CameraBoom->bUsePawnControlRotation = true;
	/*
	* This is going to rotate the arm based on the controller and arm is our cameraboom.
	*/

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	/*
	* We Created the UCameraComponent's subobject to use camera component
	*/
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	/*
	* We bound FollowCamera to CameraBoom because, Cameraboom is holding the camera 
	And we have to specify to how to adjust the controller rotation and USpringArmComponent does that for us!
	*/

	FollowCamera->bUsePawnControlRotation = false;
	/*
	* This one is going to false because we gave controll to the CameraBoom
	*/



}


// Called when the game starts or when spawned
void AMainChar_Movement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainChar_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainChar_Movement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

			/*
			* Now we are going to bind the Key component which we are designed 
			at Unreal Engine -> Edit -> Project Settings -> Engine -> Input -> Action Mappings and Axis Mappings
			*/
	PlayerInputComponent->BindAxis("Turns", this, &APawn::AddControllerYawInput);
	/*
	* ThisAddControllerYawInput is going to control the Yaw Rotation of our Character.
	* -->>> MAKE SURE YOUR AXIS VARIABLE NAMES MATCHES THE BindAxis's first variable, Mine is "Turns" at UnrealEngine inputs and here.
	*/

	PlayerInputComponent->BindAxis("LookUporDown", this, &APawn::AddControllerPitchInput);
	/*
	* As you realized, this is going to make AddControllerPitchInput make to able to control Pitch Rotation of our Character.
	*/

	PlayerInputComponent->BindAction("JumpUp", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("JumpUp", IE_Released, this, &ACharacter::StopJumping);
	/*
	* Just guess what we have done over here :D
	* Yeah yeah i know, easy peasy. 
	* We just added JumpUp when IE_Pressed & Don't Jump when IE_Released to our BindAction method 
	*/

	/*
	* PS: As you can see there is a little difference between BindAction and BindAxis methods
	* Which is we include our key to our BindAction method instead of this parameter in BindAxis.
	*/

	/*
	* ----> WE DID NOT DECLARED MoveUp or MoveDown methods in MainChar_Movement.h because Jumping methods are already in our character. Beautyness of Unreal Engine, right?
	*/

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainChar_Movement::MoveForwardorBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainChar_Movement::MoveRightorLeft);



}


void AMainChar_Movement::MoveForwardorBack(float Axis)
{

	//Aaand here it is. Here lies the method who allows us go forward or go back.
	FRotator Rotation = Controller->GetControlRotation();
	/*
	* In here we bound Rotation with our Controller rotation
	*/
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	/*
	* In here we declared we are only changing Yaw rotation, other ones are stable as 0.0f
	*/

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	/*
	* EAxis::X -> is making us move at the direction X!
	*/

	AddMovementInput(Direction, Axis);
	/*
	* Going forward or Back? This one is decides for us!
	*/



}

void AMainChar_Movement::MoveRightorLeft(float Axis)
{
	//Aaand here it is. Here lies the method who allows us go right or go left.

	
	FRotator Rotation = Controller->GetControlRotation();
	/*
	* In here we bound Rotation with our Controller rotation
	*/
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	/*
	* In here we declared we are only changing Yaw rotation, other ones are stable as 0.0f
	*/

	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	/*
	* EAxis::X -> is making us move at the direction Y!
	*/

	AddMovementInput(Direction, Axis);
	/*
	* Going right or left? This one is decides for us!
	*/

}