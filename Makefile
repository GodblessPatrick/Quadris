CXX=g++
CXXFLAGS=-std=c++14 -Wall -Werror -MMD -g
OBJECTS=main.o QuadrisException.o Rectangle2D.o Cell.o Block.o StarBlock.o IBlock.o JBlock.o LBlock.o OBlock.o SBlock.o ZBlock.o TBlock.o Subject.o Model.o Observer.o TextView.o Board.o Level.o Level0.o Level1.o Level2.o Level3.o Level4.o BlockFactory.o Command.o CommandInterpreter.o CompositeCommand.o MoveCommand.o LeftCommand.o RightCommand.o DownCommand.o ClockwiseCommand.o CounterClockwiseCommand.o LevelUpCommand.o LevelDownCommand.o DropCommand.o RandomCommand.o NoRandomCommand.o ReplaceCommand.o ICommand.o JCommand.o LCommand.o OCommand.o SCommand.o ZCommand.o TCommand.o RestartCommand.o HintCommand.o Reward.o GraphicsView.o Window.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean
clean:
	rm *.o ${EXEC}

.PHONY: run
run: ${EXEC}
	./${EXEC}
