#############################################################################
# CLEAN make target to remove products of build process
#############################################################################
dist_clean:
	@-if exist $(DISTDIR) $(GIT) clean -ffxd $(DISTDIR)

build_clean:
	@-if exist $(BUILDDIR_ROOT) $(GIT) clean -ffxd $(BUILDDIR_ROOT)

.PHONY : clean
clean: user_clean dist_clean build_clean
	@echo Cleanup done.

