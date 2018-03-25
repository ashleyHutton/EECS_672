CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL

OBJS = project2.o Couch.o Floor.o Wall.o Table.o Book.o Bookshelf.o Lamp.o ModelView_Additions.o

project2: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o project2 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

project2.o: project2.c++
	$(CPP) $(C_FLAGS) project2.c++
ModelView_Additions.o: ModelView_Additions.c++
	$(CPP) $(C_FLAGS) ModelView_Additions.c++
Couch.o: Couch.h Couch.c++
	$(CPP) $(C_FLAGS) Couch.c++
Floor.o: Floor.h Floor.c++
	$(CPP) $(C_FLAGS) Floor.c++
Wall.o: Wall.h Wall.c++
	$(CPP) $(C_FLAGS) Wall.c++
Table.o: Table.h Table.c++
	$(CPP) $(C_FLAGS) Table.c++
Book.o: Book.h Book.c++
	$(CPP) $(C_FLAGS) Book.c++
Bookshelf.o: Bookshelf.h Bookshelf.c++
	$(CPP) $(C_FLAGS) Bookshelf.c++
Lamp.o: Lamp.h Lamp.c++
	$(CPP) $(C_FLAGS) Lamp.c++