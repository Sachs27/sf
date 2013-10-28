LOCAL_PATH := $(call my-dir)/src

include $(CLEAR_VARS)

LOCAL_MODULE := sf

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_SRC_FILES :=	\
	sf_array.c		\
	sf_list.c		\
	sf_utils.c

LOCAL_CFLAGS := -DANDROID

include $(BUILD_STATIC_LIBRARY)
