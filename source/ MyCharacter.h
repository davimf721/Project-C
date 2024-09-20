// MyCharacter.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class YOURPROJECT_API AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Construtor
    AMyCharacter();

protected:
    // Função chamada quando o jogo começa
    virtual void BeginPlay() override;

public:
    // Chamado a cada frame
    virtual void Tick(float DeltaTime) override;

    // Setup para o sistema de controle de entrada
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Funções de movimentação
    void MoveRight(float Value);
    
    // Função de pulo
    virtual void Jump() override;   // Sobrescreve a função de pulo padrão
    virtual void StopJumping() override;

    // Funções de corrida
    void StartSprinting();          // Inicia a corrida
    void StopSprinting();           // Para a corrida

private:
    // Variáveis de controle
    float WalkSpeed;    // Velocidade de caminhada normal
    float SprintSpeed;  // Velocidade de corrida
    bool bIsSprinting;  // Indica se o jogador está correndo

    // Sistema de pulo duplo
    int JumpCount;      // Contador de pulos (para controlar o pulo duplo)
    int MaxJumpCount;   // Máximo de pulos permitidos (2 para pulo duplo)

    // Atributos do personagem
    int Strength;       // Força - afeta a vida
    int Intelligence;   // Inteligência - afeta a mana
    int Agility;        // Agilidade - afeta a velocidade de movimento

    // Atributos derivados
    float MaxHealth;    // Quantidade máxima de vida, modificada pela Força
    float CurrentHealth;// Quantidade atual de vida
    float MaxMana;      // Quantidade máxima de mana, modificada pela Inteligência
    float CurrentMana;  // Quantidade atual de mana

    // Funções para atualizar os atributos derivados com base nos atributos primários
    void UpdateAttributes();
    
};