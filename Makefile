.PHONY: clean All

All:
	@echo "----------Building project:[ ProgrammingArt - Debug ]----------"
	@cd "ProgrammingArt" && $(MAKE) -f  "ProgrammingArt.mk"
clean:
	@echo "----------Cleaning project:[ ProgrammingArt - Debug ]----------"
	@cd "ProgrammingArt" && $(MAKE) -f  "ProgrammingArt.mk" clean
