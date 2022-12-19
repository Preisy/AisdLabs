CC = gcc -std=c99
CFlags = -Isrc
Src = main.c \
	src/readMatrix.c \
	src/printMatrix.c \
	src/processMatrix.c \
	src/Matrix.c

BuildDir = build
Obj = $(addprefix $(BuildDir)/,$(subst /,_,$(patsubst %.c,%.o,$(Src))))

override MY_MAKE_INVOCATION_CMD_LINE:=$(MAKE) -C $(CURDIR) $(if $(MY_MAKEFILE),-f $(MY_MAKEFILE),) --no-print-directory



all:
	@mkdir -p $(BuildDir)
	@$(MY_MAKE_INVOCATION_CMD_LINE) run

run: $(Obj)
	@($(CC) $(Obj) -o main)
	@echo "Linked: " main


define CC_RULE =
$(BuildDir)/$(subst /,_,$(patsubst %c,%o,$(Source))): $(Source)
	@($(CC) $(CFlags) -c $(Source) -o $(BuildDir)/$(subst /,_,$(patsubst %c,%o,$(Source))))
	@echo "Complied: " $(Source)
endef

$(foreach Source,$(Src),$(eval $(call CC_RULE,$(Source))))



clean:
	rm -rf $(BuildDir)/*.o












