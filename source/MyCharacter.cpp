// MyCharacter.cpp

#include "MyCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Construtor
AMyCharacter::AMyCharacter()
{
    // Definir as propriedades iniciais
    PrimaryActorTick.bCanEverTick = true;  // Ativar o tick por frame

    // Inicializando os atributos
    Strength = 0;        // Valor padrão para Força
    Intelligence = 0;    // Valor padrão para Inteligência
    Agility = 0;         // Valor padrão para Agilidade

    // Inicializando os atributos derivados
    MaxHealth = 100.0f;   // Vida base
    CurrentHealth = MaxHealth;
    MaxMana = 50.0f;      // Mana base
    CurrentMana = MaxMana;

     // Velocidade padrão, será modificada pela Agilidade
    WalkSpeed = 450.0f;   
    SprintSpeed = 900.0f;
    bIsSprinting = false;

    // Inicializando o sistema de pulo duplo
    JumpCount = 0;
    JumpForce = 500.0f;  // Força do salto
    MaxJumpCount = 2;       // Definimos que o jogador pode pular no máximo 2 vezes (pulo duplo)

    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;  // Inicialmente, use a velocidade de caminhada
    GetCharacterMovement()->AirControl = 0.8f;        // Controle aéreo para melhor movimentação durante o pulo

    // Atualiza os atributos iniciais com base nos valores padrão
    UpdateAttributes();
    
}

// Função para atualizar os atributos derivados com base nos atributos primários
void AMyCharacter::UpdateAttributes()
{
    // Força afeta a vida (cada ponto de força aumenta a vida em 10)
    MaxHealth = 100.0f + Strength * 10.0f;
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);  // Garanta que a vida atual nunca exceda o máximo

    // Inteligência afeta a mana (cada ponto de inteligência aumenta a mana em 5)
    MaxMana = 50.0f + Intelligence * 5.0f;
    CurrentMana = FMath::Clamp(CurrentMana, 0.0f, MaxMana);        // Garanta que a mana atual nunca exceda o máximo

    // Agilidade afeta a velocidade de movimento (cada ponto de agilidade aumenta a velocidade em 5)
    WalkSpeed = 450.0f + Agility * 5.0f;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;               // Atualiza a velocidade de movimento
    SprintSpeed = WalkSpeed * 2.0f;                                 // Sprint é o dobro da velocidade normal
}

// Chamada quando o jogo começa ou quando o personagem é spawnado
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Chamado a cada frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

     // Verifica se o personagem está no chão
    if (GetCharacterMovement()->IsMovingOnGround())
    {
        JumpCount = 0;  // Se o personagem tocar o chão, o contador de pulos é resetado
    }
}

// Configurar o mapeamento de inputs
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Mapeamento das teclas de movimento (WASD)
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);  // A e D
    PlayerInputComponent->BindAxis("MoveUp", this, &AMyCharacter::MoveUp);        // W e S (se precisar de movimentação vertical)

    // Mapeamento para a corrida - Shift para correr
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::StartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopSprinting);

   // Pulo - com tecla Barra de Espaço
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
}

// Função para mover o personagem para os lados (A e D)
void AMyCharacter::MoveRight(float Value)
{
    // Adiciona movimento horizontal com base no valor de entrada
    AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

// Inicia a corrida (Shift pressionado)
void AMyCharacter::StartSprinting()
{
    bIsSprinting = true;
    GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;  // Aumenta a velocidade para corrida
}

// Para a corrida (Shift solto)
void AMyCharacter::StopSprinting()
{
    bIsSprinting = false;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;  // Volta para a velocidade normal de caminhada
}

// Sobrescreve a função de pulo
void AMyCharacter::Jump()
{
    // Verifica se o personagem pode pular (pulo simples ou duplo)
    if (JumpCount < MaxJumpCount)
    {
        // Incrementa o contador de pulos
        JumpCount++;

        // Chama a função de pulo original
        ACharacter::Jump();
    }
}

// Sobrescreve a função de parar o pulo
void AMyCharacter::StopJumping()
{
    // Chama a função padrão de parar o pulo
    ACharacter::StopJumping();
}