depend: depend-recursive $(OBJS:.o=.d)

#ifneq ($(strip $(OBJS)),)
#-include $(OBJS:%.o=.dep/%.d)
#endif
