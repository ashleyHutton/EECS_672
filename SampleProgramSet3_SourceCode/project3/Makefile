CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../imageutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libimage.so ../lib/libmvc.so
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL

OBJS = project3.o Couch.o Floor.o Wall.o Table.o Book.o Bookshelf.o Lamp.o Pillow.o ModelView_Additions.o PhongMaterial.o SceneElement.o

project3: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o project3 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libimage.so: ../imageutil/ImageReader.h ../imageutil/ImageReader.c++
	(cd ../imageutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

project3.o: project3.c++
	$(CPP) $(C_FLAGS) project3.c++
ModelView_Additions.o: ModelView_Additions.c++
	$(CPP) $(C_FLAGS) ModelView_Additions.c++
PhongMaterial.o: PhongMaterial.c++
	$(CPP) $(C_FLAGS) PhongMaterial.c++
SceneElement.o: SceneElement.h SceneElement.c++
	$(CPP) $(C_FLAGS) SceneElement.c++
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
Pillow.o: Pillow.h Pillow.c++
	$(CPP) $(C_FLAGS) Pillow.c++