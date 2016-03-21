INCLUDE_PATH=../vsd_driver/
SHARE_PATH=../../../../vm/share/

vsd_userspace: main.c $(INCLUDE_PATH)/vsd_ioctl.h
	gcc $< -I$(INCLUDE_PATH) -o $@
	cp $@ $(SHARE_PATH)

.PHONY: clean

clean:
	rm -rf vsd_userspace
