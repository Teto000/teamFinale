xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 140;
 -263.59478;2206.22640;-274.13257;,
 263.59478;2206.22640;-274.13257;,
 263.59478;1466.18030;-274.13257;,
 -263.59478;1466.18030;-274.13257;,
 263.59478;2206.22640;-274.13257;,
 263.59478;2206.22640;253.05884;,
 263.59478;1466.18030;253.05884;,
 263.59478;1466.18030;-274.13257;,
 263.59478;2206.22640;253.05884;,
 -263.59478;2206.22640;253.05884;,
 -263.59478;1466.18030;253.05884;,
 263.59478;1466.18030;253.05884;,
 -263.59478;2206.22640;253.05884;,
 -263.59478;2206.22640;-274.13257;,
 -263.59478;1466.18030;-274.13257;,
 -263.59478;1466.18030;253.05884;,
 263.59478;2206.22640;-274.13257;,
 -263.59478;2206.22640;-274.13257;,
 -263.59478;1466.18030;-274.13257;,
 263.59478;1466.18030;-274.13257;,
 -10.00000;2168.92718;-10.00000;,
 10.00000;2168.92718;-10.00000;,
 10.00000;2148.92718;-10.00000;,
 -10.00000;2148.92718;-10.00000;,
 10.00000;2168.92718;-10.00000;,
 10.00000;2168.92718;10.00000;,
 10.00000;2148.92718;10.00000;,
 10.00000;2148.92718;-10.00000;,
 10.00000;2168.92718;10.00000;,
 -10.00000;2168.92718;10.00000;,
 -10.00000;2148.92718;10.00000;,
 10.00000;2148.92718;10.00000;,
 -10.00000;2168.92718;10.00000;,
 -10.00000;2168.92718;-10.00000;,
 -10.00000;2148.92718;-10.00000;,
 -10.00000;2148.92718;10.00000;,
 10.00000;2168.92718;-10.00000;,
 -10.00000;2168.92718;-10.00000;,
 -10.00000;2148.92718;-10.00000;,
 10.00000;2148.92718;-10.00000;,
 -218.08518;2256.15179;-227.39229;,
 218.08518;2256.15179;-227.39229;,
 218.08518;2180.78109;-227.39229;,
 -218.08518;2180.78109;-227.39229;,
 218.08518;2256.15179;-227.39229;,
 218.08518;2256.15179;208.77808;,
 218.08518;2180.78109;208.77808;,
 218.08518;2180.78109;-227.39229;,
 218.08518;2256.15179;208.77808;,
 -218.08518;2256.15179;208.77808;,
 -218.08518;2180.78109;208.77808;,
 218.08518;2180.78109;208.77808;,
 -218.08518;2256.15179;208.77808;,
 -218.08518;2256.15179;-227.39229;,
 -218.08518;2180.78109;-227.39229;,
 -218.08518;2180.78109;208.77808;,
 218.08518;2256.15179;-227.39229;,
 -218.08518;2256.15179;-227.39229;,
 -218.08518;2180.78109;-227.39229;,
 218.08518;2180.78109;-227.39229;,
 -185.91394;2315.65140;-195.22107;,
 185.91394;2315.65140;-195.22107;,
 185.91394;2251.39906;-195.22107;,
 -185.91394;2251.39906;-195.22107;,
 185.91394;2315.65140;-195.22107;,
 185.91394;2315.65140;176.60684;,
 185.91394;2251.39906;176.60684;,
 185.91394;2251.39906;-195.22107;,
 185.91394;2315.65140;176.60684;,
 -185.91394;2315.65140;176.60684;,
 -185.91394;2251.39906;176.60684;,
 185.91394;2251.39906;176.60684;,
 -185.91394;2315.65140;176.60684;,
 -185.91394;2315.65140;-195.22107;,
 -185.91394;2251.39906;-195.22107;,
 -185.91394;2251.39906;176.60684;,
 185.91394;2315.65140;-195.22107;,
 -185.91394;2315.65140;-195.22107;,
 -185.91394;2251.39906;-195.22107;,
 185.91394;2251.39906;-195.22107;,
 -15.98120;2734.68891;-25.28831;,
 15.98120;2734.68891;-25.28831;,
 15.98120;2262.28851;-25.28831;,
 -15.98120;2262.28851;-25.28831;,
 15.98120;2734.68891;-25.28831;,
 15.98120;2734.68891;6.67406;,
 15.98120;2262.28851;6.67406;,
 15.98120;2262.28851;-25.28831;,
 15.98120;2734.68891;6.67406;,
 -15.98120;2734.68891;6.67406;,
 -15.98120;2262.28851;6.67406;,
 15.98120;2262.28851;6.67406;,
 -15.98120;2734.68891;6.67406;,
 -15.98120;2734.68891;-25.28831;,
 -15.98120;2262.28851;-25.28831;,
 -15.98120;2262.28851;6.67406;,
 15.98120;2734.68891;-25.28831;,
 -15.98120;2734.68891;-25.28831;,
 -15.98120;2262.28851;-25.28831;,
 15.98120;2262.28851;-25.28831;,
 -263.59478;1465.47014;-274.13257;,
 263.59478;1465.47014;-274.13257;,
 263.59478;725.42403;-274.13257;,
 -263.59478;725.42403;-274.13257;,
 263.59478;1465.47014;-274.13257;,
 263.59478;1465.47014;253.05884;,
 263.59478;725.42403;253.05884;,
 263.59478;725.42403;-274.13257;,
 263.59478;1465.47014;253.05884;,
 -263.59478;1465.47014;253.05884;,
 -263.59478;725.42403;253.05884;,
 263.59478;725.42403;253.05884;,
 -263.59478;1465.47014;253.05884;,
 -263.59478;1465.47014;-274.13257;,
 -263.59478;725.42403;-274.13257;,
 -263.59478;725.42403;253.05884;,
 263.59478;1465.47014;-274.13257;,
 -263.59478;1465.47014;-274.13257;,
 -263.59478;725.42403;-274.13257;,
 263.59478;725.42403;-274.13257;,
 -263.59478;736.65763;-274.13257;,
 263.59478;736.65763;-274.13257;,
 263.59478;-3.38779;-274.13257;,
 -263.59478;-3.38779;-274.13257;,
 263.59478;736.65763;-274.13257;,
 263.59478;736.65763;253.05884;,
 263.59478;-3.38779;253.05884;,
 263.59478;-3.38779;-274.13257;,
 263.59478;736.65763;253.05884;,
 -263.59478;736.65763;253.05884;,
 -263.59478;-3.38779;253.05884;,
 263.59478;-3.38779;253.05884;,
 -263.59478;736.65763;253.05884;,
 -263.59478;736.65763;-274.13257;,
 -263.59478;-3.38779;-274.13257;,
 -263.59478;-3.38779;253.05884;,
 263.59478;736.65763;-274.13257;,
 -263.59478;736.65763;-274.13257;,
 -263.59478;-3.38779;-274.13257;,
 263.59478;-3.38779;-274.13257;;
 
 42;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;;
 
 MeshMaterialList {
  3;
  42;
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/Game/bill003.png";
   }
  }
  Material {
   0.800000;0.728000;0.608800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/Game/block008.png";
   }
  }
  Material {
   0.235200;0.235200;0.235200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  42;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;;
 }
 MeshTextureCoords {
  140;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
