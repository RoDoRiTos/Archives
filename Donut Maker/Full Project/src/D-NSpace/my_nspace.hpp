#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/Texture.h"
#include "cinder/TriMesh.h"
#include "cinder/CinderMath.h"


namespace doritos{
  enum Window{
    WIDTH = 640,
    HEIGHT = 640
  };

  struct Object{
    ci::Vec3f pos;
    ci::Vec3f rotation;
  };

  class Plane{
  private:
    ci::TriMesh plane;
  public:
    void init(){
      ci::Vec3f plane_vertices[] = {
        { -1, 1, 0 }, { 1, 1, 0 },
        { 1, -1, 0 }, { -1, -1, 0 },
      };

      plane.appendVertices(plane_vertices, sizeof(plane_vertices) / sizeof(plane_vertices[0]));

      ci::ColorA plane_colors[]{
        {1, 1, 1, 1}, { 1, 1, 1, 1 },
        { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
      };

      plane.appendColorsRgba(plane_colors, sizeof(plane_colors) / sizeof(plane_colors[0]));

      uint32_t plane_indices[] = {
        0, 1, 2,
        2, 3, 0
      };

      plane.appendIndices(plane_indices, sizeof(plane_indices) / sizeof(plane_indices[0]));

      ci::Vec2f plane_tex_coords[] = {
        { 0, 0 }, { 1, 0 },
        { 1, 1 }, { 0, 1 }
      };

      plane.appendTexCoords(plane_tex_coords, sizeof(plane_tex_coords) / sizeof(plane_tex_coords[0]));
    }

    ci::TriMesh getMesh(){
      return plane;
    }
  };

  class Func{
  public:
    static std::string getNumberSize(unsigned short counter){
      unsigned short size = counter / 3;
      switch (size){
      case 1:
        return "K";
      case 2:
        return "M";
      case 3:
        return "B";
      case 4:
        return "T";
      case 5:
        return "Qa";
      }
      return "";
    }

    static std::string filterValue(unsigned __int64 value){
      unsigned __int64 init_val = value;
      if (value > 1000){
        short counter = -1;
        std::vector<unsigned short> temp;
        while (value > 0){
          temp.push_back(value % 10);
          value /= 10;
          counter++;
        }
        unsigned short size = counter / 3;
        unsigned short disp_val = static_cast<unsigned short>(init_val / ci::math<unsigned __int64>::pow(10, size * 3));
        unsigned short dec = static_cast<unsigned short>((init_val / ci::math<int>::pow(10, size * 3 - 3)) % 1000);
        std::stringstream disp_dec;
        if (dec < 10){
          disp_dec << "00" << dec;
        }
        else if (dec < 100){
          disp_dec << "0" << dec;
        }
        else{
          disp_dec << dec;
        }
        return std::to_string(disp_val) + "." + disp_dec.str() + " " + getNumberSize(counter);
      }
      return std::to_string(value);
    }
  };
}