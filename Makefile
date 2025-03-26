# =======================================================
#                 Hoochamacallit Makefile
# =======================================================

.PHONY: all clean



# SubDir path
COMMON_DIR = Common
DR_DIR = DR
DX_DIR = DX
DC_DIR = DC



# Common/bin for put DX and DR into same directory 
COMMON_BIN = $(COMMON_DIR)/bin



# Targets Executable Files
DR_TARGET = $(COMMON_BIN)/DR
DX_TARGET = $(COMMON_BIN)/DX
DC_TARGET = $(DC_DIR)/bin/DC



all:
	@echo "SetUp Common Directory..."
	$(MAKE) -C $(COMMON_DIR)
	
	@echo ""
	@echo "Building DR application..."
	$(MAKE) -C $(DR_DIR)
	
	@echo ""
	@echo "Building DX application..."
	$(MAKE) -C $(DX_DIR)
	
	@echo ""
	#echo "Building DC application..."
	$(MAKE) -C $(DC_DIR)
	
	@echo ""
	@echo "Copying DR and DX to same directory (Common/bin)..."
	cp $(DR_DIR)/bin/DR $(COMMON_BIN)/
	cp $(DX_DIR)/bin/DX $(COMMON_BIN)/
	

clean:
	$(MAKE) -C $(COMMON_DIR) clean
	@echo ""
	$(MAKE) -C $(DR_DIR) clean
	@echo ""
	$(MAKE) -C $(DX_DIR) clean
	@echo ""
	$(MAKE) -C $(DC_DIR) clean
