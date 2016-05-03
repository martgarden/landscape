#include "texture.hpp"

namespace marrow {
    Texture::Texture() {;}

    Texture::Texture(const char * file_name) {
        *this = loadFromFile(file_name);
    }

    Texture::Texture &operator =(const Texture &rhs) {
        _tex_id = rhs._tex_id;
        _type = rhs._type;
    }

    bool LoadAndSetTexture(const char *filename, GLenum target) {
        // Create IL image
        ILuint IL_tex;
        ilGenImages(1, &IL_tex);

        ilBindImage(IL_tex);

        // Solve upside down textures
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT); 

        // Load IL image
        ILboolean success = ilLoadImage(filename);
        if (!success) {
            ilBindImage(0);
            ilDeleteImages(1, &IL_tex); 
            cout << "Couldn't load texture: " << filename;
            return false;
        }

        // Get IL image parameters
        int img_width = ilGetInteger(IL_IMAGE_WIDTH);
        int img_height = ilGetInteger(IL_IMAGE_HEIGHT);
        int img_format = ilGetInteger(IL_IMAGE_FORMAT);
        int img_type = ilGetInteger(IL_IMAGE_TYPE);

        // Choose internal format, format, and type for glTexImage2D
        GLint internal_format = 0;
        GLenum format = 0;
        GLenum type = img_type;            // IL constants matches GL constants
        switch (img_format) {
        case IL_RGB:    internal_format = GL_RGB;    format = GL_RGB;    break;
        case IL_RGBA:    internal_format = GL_RGBA;    format = GL_RGBA;    break;
        case IL_BGR:    internal_format = GL_RGB;    format = GL_BGR;    break;
        case IL_BGRA:    internal_format = GL_RGBA;    format = GL_BGRA;    break;
        case IL_COLOR_INDEX:
        case IL_ALPHA:
        case IL_LUMINANCE:
        case IL_LUMINANCE_ALPHA:
            // Unsupported format
            ilBindImage(0);
            ilDeleteImages(1, &IL_tex); 
            printf("Texture %S has unsupported format\n", filename);
            return false;
        }

        // Set the data to OpenGL (assumes texture object is already bound)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(target, 0, internal_format, img_width, img_height, 0, format, type, ilGetData());

        // Unset and delete IL texture
        ilBindImage(0);
        ilDeleteImages(1, &IL_tex);

        return true;
    }

    Texture Texture::loadFromFile(const char * file_name) {
        // Create OpenGL texture object
        Texture tex;
        tex._type = GL_TEXTURE_2D;
        glGenTextures(1, &tex._tex_id);
        glBindTexture(GL_TEXTURE_2D, tex._tex_id);

        // Load the data into OpenGL texture object
        if (!LoadAndSetTexture(filename, GL_TEXTURE_2D)) {
            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteTextures(1, &tex._tex_id);
            return 0;
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        return tex;
    }

    Texture Texture::loadCubeFromFiles(const char * file_prefix) {
        // Create OpenGL texture object
        Texture tex;
        tex._type = GL_TEXTURE_CUBE_MAP;
        glGenTextures(1, &tex._tex_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, tex._tex_id);
        string name_string(file_prefix);

        // Load the data into OpenGL texture object
        if (
            !LoadAndSetTexture((name_string + "R").c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_X) ||
            !LoadAndSetTexture((name_string + "L").c_str(), GL_TEXTURE_CUBE_MAP_NEGATIVE_X) ||
            !LoadAndSetTexture((name_string + "U").c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_Y) ||
            !LoadAndSetTexture((name_string + "D").c_str(), GL_TEXTURE_CUBE_MAP_NEGATIVE_Y) ||
            !LoadAndSetTexture((name_string + "F").c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_Z) ||
            !LoadAndSetTexture((name_string + "B").c_str(), GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            glDeleteTextures(1, &tex._tex_id);
            return 0;
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        return tex;
    }

    void Texture::set() {
        glBindTexture(_type, _tex_id);
    }

    void Texture::unset() {
        glBindTexture(_type, 0);
    }

    void Texture::setRepeat(bool set) {
        if(set) set();
        glTexParametri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParametri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        else(set) unset();
    }

    void Texture::setClamp();
        if(set) set();
        glTexParametri(_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParametri(_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        else(set) unset();
    }

}
