// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <ctime>
#include "hidden_word_list.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);
    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{   

    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }



}


void UBullCowCartridge::SetupGame()
{
    Menu();
    
    
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();

    

    // PrintLine(FString::Printf(TEXT("The hidden word is: %s"), *HiddenWord)); // Debug Line
    PrintLine(TEXT("You have %i lives,"), Lives);
    PrintLine(TEXT("And your task is to guess %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("Press 1 for explanation of the game"));
    PrintLine(TEXT("Make a guess and press ENTER to continue!"));

    bGameOver = false;
}


void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press ENTER to play again!"));
}


void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("Correct!"));
        EndGame();
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters!"));
    }
    
    FBullCowCount Count = GetBullCows(Guess);
    PrintLine(TEXT("You have %i bulls and %i cows"), Count.Bulls, Count.Cows);

    if(HiddenWord.Len() == Guess.Len())
    {
        return;
    }

        Lives--;

        if(Lives <= 0)
        {       
            ClearScreen();
            PrintLine(TEXT("You have no lives left"));  
            PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
            EndGame();
            return;
        }

    
    if(HiddenWord.Len() != Guess.Len())
    {
        PrintLine(TEXT("Wrong number of letters,\nword has %i letters!"), HiddenWord.Len());
        PrintLine(TEXT("Now you have %i lives,\ntry guessing again"), Lives);
        return;
    }

        
}


bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for(int32 i = 0; i < Word.Len() - 1; i++)
    {
        for(int32 j = i + 1; j < Word.Len(); j++)
        {
            if(Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    

    for(FString OneWord : WordList)
    {
        if(OneWord.Len() >= 4 && OneWord.Len() <= 8 && IsIsogram(OneWord))
        {
            ValidWords.Emplace(OneWord);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for(int32 i = 0; i < Guess.Len(); i++)
    {
        if((Guess.Len() > i && HiddenWord.Len() > i) && Guess[i] == HiddenWord[i])
        {
            Count.Bulls++;
            continue;
        }

        for(int32 j = 0; j < HiddenWord.Len(); j++)
        {
            if((Guess.Len() > j && HiddenWord.Len() > j) && Guess[i] == HiddenWord[j])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}












void UBullCowCartridge::Menu()
{
    srand(time(NULL));
    int slucaj = rand()%10;

    if(slucaj == 0)
    {
        PrintLine(TEXT("It is those who possess wisdom who are the greatest fools. History has shown us     this. You could say that this is the final warning from God to those who resist."));
    }
    if (slucaj == 1)
    {
        PrintLine(TEXT("Remembering something that no one else can is a painful thing. You can’t talk to anyone about it. No one will understand you. You’ll be alone."));
    }
    if(slucaj == 2)
    {
        PrintLine(TEXT("The”‘present” is a leaf floating on top of the river. It moves along with the flow from past to future."));
    }
    if(slucaj == 3)
    {
        PrintLine(TEXT("It feels like time is passing so quickly. Damn you, Einstein! Your science is crowding in on our kiss! He was right. The passage of time depends entirely on where you’re standing. Relativity Theory… it’s so romantic. But it’s just so tragic too."));
    }
    if(slucaj == 4)
    {
        PrintLine(TEXT("Maybe there are copies of me on countless world lines. Maybe all their minds are connected, forming a single “me.” That sounds wonderful, don’t you think? Being in all times and in all places."));
    }
    if(slucaj == 5)
    {
        PrintLine(TEXT("People’s feelings are memories that transcend time."));
    }
    if(slucaj == 6)
    {
        PrintLine(TEXT("Everyone gets help from someone else at some point in their lives. So someday, you should help someone too."));
        
    }
    if(slucaj == 7)
    {
        PrintLine(TEXT("Everything You've Been Taught Is Based On Theories And Logic. Soon, You'll Come To Realize How Pointless They Are."));
    }
    if(slucaj == 8)
    {
        PrintLine(TEXT("Beautiful flowers, too, eventually wither and fall. That’s the fate of all living beings."));
    }
    if(slucaj == 9)
    {
        PrintLine(TEXT("An unforeseen situation… An unexpected turn of events… In the face of those, you too will face your true self."));
    }
    PrintLine(TEXT("________________________"));
}

