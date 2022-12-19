CC = g++ -std=c++11
CFlags = -ISrc -ILib
Src = main.cpp \
	  Src/View/Output.cpp \
	  Src/Models/Entities/ProcessModel.cpp \
	  Src/Controllers/ProcessScheduler/ProcessSchedulerController.cpp \
	  Src/Models/Services/ProcessScheduler/ProcessSchedulerService.cpp \
	  Src/Controllers/ProcessScheduler/Realization/RoundRobinController.cpp \
	  Src/Models/Services/ProcessScheduler/Realization/RoundRobinService.cpp

BuildDir = build
Obj = $(addprefix $(BuildDir)/,$(subst /,_,$(patsubst %.cpp,%.o,$(Src))))

override MY_MAKE_INVOCATION_CMD_LINE:=$(MAKE) -C $(CURDIR) $(if $(MY_MAKEFILE),-f $(MY_MAKEFILE),) --no-print-directory



all:
	@mkdir -p $(BuildDir)
	@$(MY_MAKE_INVOCATION_CMD_LINE) run

run: $(Obj)
	@($(CC) $(Obj) -o main)
	@#($(CC) $(Obj) -LLib -Wl,-RLib -ltest -o main)
	@echo "Linked: " main


define CC_RULE =
$(BuildDir)/$(subst /,_,$(patsubst %cpp,%o,$(Source))): $(Source)
	@($(CC) $(CFlags) -c $(Source) -o $(BuildDir)/$(subst /,_,$(patsubst %cpp,%o,$(Source))))
	@echo "Complied: " $(Source)
endef

$(foreach Source,$(Src),$(eval $(call CC_RULE,$(Source))))



clean:
	rm -rf $(BuildDir)/*.o





lib: compileLib test.o
	@(g++ test.o -LLib -Wl,-RLib -ltest -o test)
	@echo "Linked: " main

compileLib:
	g++ -std=c++14 -shared -o Lib/libtest.so -fPIC Lib/Lib.h

test.o:
	g++ -c test.cpp













