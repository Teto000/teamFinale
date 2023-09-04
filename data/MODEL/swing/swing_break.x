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
 364;
 80.97545;106.38375;15.52615;,
 80.09252;105.38670;13.38793;,
 80.09252;3.15267;81.25711;,
 80.97546;4.14972;83.39533;,
 80.92802;104.33452;11.13154;,
 80.92802;2.10048;79.00073;,
 80.92802;104.33452;11.13154;,
 83.41823;103.98118;10.37380;,
 83.41824;1.74714;78.24298;,
 80.92802;2.10048;79.00073;,
 85.85021;104.33452;11.13154;,
 85.85021;2.10048;79.00073;,
 85.85021;104.33452;11.13154;,
 86.74397;105.38670;13.38793;,
 86.74397;3.15267;81.25711;,
 85.85021;2.10048;79.00073;,
 85.90814;106.38375;15.52615;,
 85.90814;4.14972;83.39533;,
 85.90814;106.38375;15.52615;,
 83.41823;106.79220;16.40206;,
 83.41824;4.55817;84.27125;,
 85.90814;4.14972;83.39533;,
 80.97545;106.38375;15.52615;,
 80.97546;4.14972;83.39533;,
 83.41823;105.38670;13.38793;,
 83.41823;106.79220;16.40206;,
 83.41823;103.98118;10.37380;,
 80.09252;105.38670;13.38793;,
 80.97545;106.38375;15.52615;,
 80.92802;104.33452;11.13154;,
 83.41824;4.55817;84.27125;,
 83.41824;3.15267;81.25711;,
 83.41824;1.74714;78.24298;,
 80.97546;4.14972;83.39533;,
 80.09252;3.15267;81.25711;,
 80.92802;2.10048;79.00073;,
 -37.28665;44.24964;39.41167;,
 -39.33995;43.37979;38.23991;,
 47.33513;0.00330;-81.44234;,
 49.38844;0.87315;-80.27051;,
 -41.22910;44.15748;36.58988;,
 45.44588;0.78099;-83.09238;,
 -41.22910;44.15748;36.58988;,
 -41.51638;46.53873;35.51869;,
 45.15865;3.16224;-84.16343;,
 45.44588;0.78099;-83.09238;,
 -40.45595;48.88017;35.43818;,
 46.21919;5.50371;-84.24407;,
 -40.45595;48.88017;35.43818;,
 -38.29510;49.76166;36.68360;,
 48.38000;6.38517;-82.99868;,
 46.21919;5.50371;-84.24407;,
 -36.51181;48.98235;38.25752;,
 50.16323;5.60592;-81.42467;,
 -36.51181;48.98235;38.25752;,
 -36.11857;46.60263;39.40474;,
 50.55656;3.22626;-80.27751;,
 50.16323;5.60592;-81.42467;,
 -37.28665;44.24964;39.41167;,
 49.38844;0.87315;-80.27051;,
 -38.81752;46.57068;37.46170;,
 -36.11857;46.60263;39.40474;,
 -41.51638;46.53873;35.51869;,
 -39.33995;43.37979;38.23991;,
 -37.28665;44.24964;39.41167;,
 -41.22910;44.15748;36.58988;,
 50.55656;3.22626;-80.27751;,
 47.85752;3.19425;-82.22051;,
 45.15865;3.16224;-84.16343;,
 49.38844;0.87315;-80.27051;,
 47.33513;0.00330;-81.44234;,
 45.44588;0.78099;-83.09238;,
 86.67239;108.73368;15.40987;,
 86.67239;109.95471;12.11455;,
 -68.87756;147.29770;14.89790;,
 -68.87756;146.07667;18.19325;,
 86.67239;108.79930;8.63704;,
 -68.87756;146.14228;11.42042;,
 86.67239;108.79930;8.63704;,
 86.67239;105.35548;7.46923;,
 -68.87756;142.69848;10.25261;,
 -68.87756;146.14228;11.42042;,
 86.67239;101.99235;8.63704;,
 -68.87756;139.33530;11.42042;,
 86.67239;101.99235;8.63704;,
 86.67239;100.75630;12.11455;,
 -68.87756;138.09930;14.89790;,
 -68.87756;139.33530;11.42042;,
 86.67239;101.91225;15.40987;,
 -68.87756;139.25524;18.19325;,
 86.67239;101.91225;15.40987;,
 86.67239;105.35548;16.75981;,
 -68.87756;142.69848;19.54316;,
 -68.87756;139.25524;18.19325;,
 86.67239;108.73368;15.40987;,
 -68.87756;146.07667;18.19325;,
 86.67239;105.35548;12.11455;,
 86.67239;105.35548;16.75981;,
 86.67239;105.35548;7.46923;,
 86.67239;109.95471;12.11455;,
 86.67239;108.73368;15.40987;,
 86.67239;108.79930;8.63704;,
 -68.87756;142.69848;19.54316;,
 -68.87756;142.69848;14.89790;,
 -68.87756;142.69848;10.25261;,
 -68.87756;146.07667;18.19325;,
 -68.87756;147.29770;14.89790;,
 -68.87756;146.14228;11.42042;,
 -67.67945;143.72674;18.30950;,
 -68.56237;142.72968;16.17128;,
 -68.56237;3.15267;81.25711;,
 -67.67944;4.14972;83.39533;,
 -67.72687;141.67750;13.91489;,
 -67.72687;2.10048;79.00073;,
 -67.72687;141.67750;13.91489;,
 -65.23666;141.32416;13.15715;,
 -65.23666;1.74714;78.24298;,
 -67.72687;2.10048;79.00073;,
 -62.80468;141.67750;13.91489;,
 -62.80467;2.10048;79.00073;,
 -62.80468;141.67750;13.91489;,
 -61.91093;142.72968;16.17128;,
 -61.91092;3.15267;81.25711;,
 -62.80467;2.10048;79.00073;,
 -62.74675;143.72674;18.30950;,
 -62.74675;4.14972;83.39533;,
 -62.74675;143.72674;18.30950;,
 -65.23666;144.13518;19.18541;,
 -65.23666;4.55817;84.27125;,
 -62.74675;4.14972;83.39533;,
 -67.67945;143.72674;18.30950;,
 -67.67944;4.14972;83.39533;,
 -65.23666;142.72968;16.17128;,
 -65.23666;144.13518;19.18541;,
 -65.23666;141.32416;13.15715;,
 -68.56237;142.72968;16.17128;,
 -67.67945;143.72674;18.30950;,
 -67.72687;141.67750;13.91489;,
 -65.23666;4.55817;84.27125;,
 -65.23666;3.15267;81.25711;,
 -65.23666;1.74714;78.24298;,
 -67.67944;4.14972;83.39533;,
 -68.56237;3.15267;81.25711;,
 -67.72687;2.10048;79.00073;,
 -67.71067;141.73260;15.96497;,
 -68.59357;142.72968;13.82675;,
 -68.59357;3.15264;-51.25909;,
 -67.71067;2.15559;-49.12088;,
 -67.75811;143.78184;11.57036;,
 -67.75811;4.20483;-53.51548;,
 -67.75811;143.78184;11.57036;,
 -65.26789;144.13518;10.81262;,
 -65.26790;4.55817;-54.27323;,
 -67.75811;4.20483;-53.51548;,
 -62.83591;143.78184;11.57036;,
 -62.83592;4.20483;-53.51548;,
 -62.83591;143.78184;11.57036;,
 -61.94216;142.72968;13.82675;,
 -61.94216;3.15264;-51.25909;,
 -62.83592;4.20483;-53.51548;,
 -62.77799;141.73260;15.96497;,
 -62.77799;2.15559;-49.12088;,
 -62.77799;141.73260;15.96497;,
 -65.26789;141.32416;16.84088;,
 -65.26789;1.74714;-48.24496;,
 -62.77799;2.15559;-49.12088;,
 -67.71067;141.73260;15.96497;,
 -67.71067;2.15559;-49.12088;,
 -65.26789;142.72968;13.82675;,
 -65.26789;141.32416;16.84088;,
 -65.26789;144.13518;10.81262;,
 -68.59357;142.72968;13.82675;,
 -67.71067;141.73260;15.96497;,
 -67.75811;143.78184;11.57036;,
 -65.26789;1.74714;-48.24496;,
 -65.26789;3.15264;-51.25909;,
 -65.26790;4.55817;-54.27323;,
 -67.71067;2.15559;-49.12088;,
 -68.59357;3.15264;-51.25909;,
 -67.75811;4.20483;-53.51548;,
 71.89352;0.42726;15.84496;,
 72.24284;0.46086;14.89789;,
 61.77995;109.12216;14.89789;,
 61.43063;109.08856;15.84496;,
 71.91227;0.42906;13.89847;,
 61.44941;109.09032;13.89847;,
 71.91227;0.42906;13.89847;,
 70.92711;0.33417;13.56283;,
 60.46424;108.99549;13.56283;,
 61.44941;109.09032;13.89847;,
 69.96497;0.24153;13.89847;,
 59.50211;108.90282;13.89847;,
 69.96497;0.24153;13.89847;,
 69.61139;0.20748;14.89789;,
 59.14850;108.86880;14.89789;,
 59.50211;108.90282;13.89847;,
 69.94208;0.23934;15.84496;,
 59.47916;108.90061;15.84496;,
 69.94208;0.23934;15.84496;,
 70.92711;0.33417;16.23292;,
 60.46424;108.99549;16.23292;,
 59.47916;108.90061;15.84496;,
 71.89352;0.42726;15.84496;,
 61.43063;109.08856;15.84496;,
 70.92711;0.33417;14.89789;,
 70.92711;0.33417;16.23292;,
 70.92711;0.33417;13.56283;,
 72.24284;0.46086;14.89789;,
 71.89352;0.42726;15.84496;,
 71.91227;0.42906;13.89847;,
 60.46424;108.99549;16.23292;,
 60.46424;108.99549;14.89789;,
 60.46424;108.99549;13.56283;,
 61.43063;109.08856;15.84496;,
 61.77995;109.12216;14.89789;,
 61.44941;109.09032;13.89847;,
 25.93151;33.48603;15.84496;,
 26.28242;33.48603;14.89789;,
 26.28242;117.50289;14.89789;,
 25.93151;117.50289;15.84496;,
 25.95035;33.48603;13.89847;,
 25.95038;117.50289;13.89847;,
 25.95035;33.48603;13.89847;,
 24.96062;33.48603;13.56283;,
 24.96062;117.50289;13.56283;,
 25.95038;117.50289;13.89847;,
 23.99405;33.48603;13.89847;,
 23.99405;117.50289;13.89847;,
 23.99405;33.48603;13.89847;,
 23.63882;33.48603;14.89789;,
 23.63882;117.50289;14.89789;,
 23.99405;117.50289;13.89847;,
 23.97104;33.48603;15.84496;,
 23.97104;117.50289;15.84496;,
 23.97104;33.48603;15.84496;,
 24.96062;33.48603;16.23292;,
 24.96062;117.50289;16.23292;,
 23.97104;117.50289;15.84496;,
 25.93151;33.48603;15.84496;,
 25.93151;117.50289;15.84496;,
 24.96062;33.48603;14.89789;,
 24.96062;33.48603;16.23292;,
 24.96062;33.48603;13.56283;,
 26.28242;33.48603;14.89789;,
 25.93151;33.48603;15.84496;,
 25.95035;33.48603;13.89847;,
 24.96062;117.50289;16.23292;,
 24.96062;117.50289;14.89789;,
 24.96062;117.50289;13.56283;,
 25.93151;117.50289;15.84496;,
 26.28242;117.50289;14.89789;,
 25.95038;117.50289;13.89847;,
 -8.97016;25.08075;15.84496;,
 -8.65750;24.92145;14.89789;,
 -7.22383;125.81577;14.89789;,
 -7.57474;125.81577;15.84496;,
 -8.95336;25.07220;13.89847;,
 -7.55587;125.81577;13.89847;,
 -8.95336;25.07220;13.89847;,
 -9.83524;25.52151;13.56283;,
 -8.54560;125.81577;13.56283;,
 -7.55587;125.81577;13.89847;,
 -10.69645;25.96032;13.89847;,
 -9.51220;125.81577;13.89847;,
 -10.69645;25.96032;13.89847;,
 -11.01295;26.12160;14.89789;,
 -9.86740;125.81577;14.89789;,
 -9.51220;125.81577;13.89847;,
 -10.71697;25.97079;15.84496;,
 -9.53521;125.81577;15.84496;,
 -10.71697;25.97079;15.84496;,
 -9.83524;25.52151;16.23292;,
 -8.54560;125.81577;16.23292;,
 -9.53521;125.81577;15.84496;,
 -8.97016;25.08075;15.84496;,
 -7.57474;125.81577;15.84496;,
 -9.83524;25.52151;14.89789;,
 -9.83524;25.52151;16.23292;,
 -9.83524;25.52151;13.56283;,
 -8.65750;24.92145;14.89789;,
 -8.97016;25.08075;15.84496;,
 -8.95336;25.07220;13.89847;,
 -8.54560;125.81577;16.23292;,
 -8.54560;125.81577;14.89789;,
 -8.54560;125.81577;13.56283;,
 -7.57474;125.81577;15.84496;,
 -7.22383;125.81577;14.89789;,
 -7.55587;125.81577;13.89847;,
 -40.19278;38.92353;15.84496;,
 -39.88013;38.75772;14.89789;,
 -42.26582;134.00466;14.89789;,
 -42.61672;134.00466;15.84496;,
 -40.17598;38.91462;13.89847;,
 -42.59785;134.00466;13.89847;,
 -40.17598;38.91462;13.89847;,
 -41.05786;39.38226;13.56283;,
 -43.58758;134.00466;13.56283;,
 -42.59785;134.00466;13.89847;,
 -41.91907;39.83889;13.89847;,
 -44.55415;134.00466;13.89847;,
 -41.91907;39.83889;13.89847;,
 -42.23560;40.00674;14.89789;,
 -44.90938;134.00466;14.89789;,
 -44.55415;134.00466;13.89847;,
 -41.93956;39.84981;15.84496;,
 -44.57719;134.00466;15.84496;,
 -41.93956;39.84981;15.84496;,
 -41.05786;39.38226;16.23293;,
 -43.58758;134.00466;16.23293;,
 -44.57719;134.00466;15.84496;,
 -40.19278;38.92353;15.84496;,
 -42.61672;134.00466;15.84496;,
 -41.05786;39.38226;14.89789;,
 -41.05786;39.38226;16.23293;,
 -41.05786;39.38226;13.56283;,
 -39.88013;38.75772;14.89789;,
 -40.19278;38.92353;15.84496;,
 -40.17598;38.91462;13.89847;,
 -43.58758;134.00466;16.23293;,
 -43.58758;134.00466;14.89789;,
 -43.58758;134.00466;13.56283;,
 -42.61672;134.00466;15.84496;,
 -42.26582;134.00466;14.89789;,
 -42.59785;134.00466;13.89847;,
 22.94720;42.43857;23.31046;,
 22.94720;42.43857;5.10586;,
 18.83141;40.47546;5.10586;,
 18.83141;40.47546;23.31046;,
 22.94720;42.43857;5.10586;,
 41.87870;2.74791;5.10586;,
 37.76291;0.78480;5.10586;,
 18.83141;40.47546;5.10586;,
 41.87870;2.74791;5.10586;,
 41.87870;2.74791;23.31046;,
 37.76291;0.78480;23.31046;,
 37.76291;0.78480;5.10586;,
 41.87870;2.74791;23.31046;,
 22.94720;42.43857;23.31046;,
 18.83141;40.47546;23.31046;,
 37.76291;0.78480;23.31046;,
 22.94720;42.43857;5.10586;,
 22.94720;42.43857;23.31046;,
 18.83141;40.47546;23.31046;,
 18.83141;40.47546;5.10586;,
 -44.33338;44.20308;23.31046;,
 -44.33338;44.20308;5.10586;,
 -46.40356;40.14006;5.10586;,
 -46.40356;40.14006;23.31046;,
 -44.33338;44.20308;5.10586;,
 -5.15188;24.23910;5.10586;,
 -7.22206;20.17608;5.10586;,
 -46.40356;40.14006;5.10586;,
 -5.15188;24.23910;5.10586;,
 -5.15188;24.23910;23.31046;,
 -7.22206;20.17608;23.31046;,
 -7.22206;20.17608;5.10586;,
 -5.15188;24.23910;23.31046;,
 -44.33338;44.20308;23.31046;,
 -46.40356;40.14006;23.31046;,
 -7.22206;20.17608;23.31046;,
 -44.33338;44.20308;5.10586;,
 -44.33338;44.20308;23.31046;,
 -46.40356;40.14006;23.31046;,
 -46.40356;40.14006;5.10586;;
 
 156;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;18,13,24,25;,
 4;13,10,26,24;,
 4;25,24,27,28;,
 4;24,26,29,27;,
 4;30,31,14,21;,
 4;31,32,11,14;,
 4;33,34,31,30;,
 4;34,35,32,31;,
 4;36,37,38,39;,
 4;37,40,41,38;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;54,55,56,57;,
 4;55,58,59,56;,
 4;54,49,60,61;,
 4;49,46,62,60;,
 4;61,60,63,64;,
 4;60,62,65,63;,
 4;66,67,50,57;,
 4;67,68,47,50;,
 4;69,70,67,66;,
 4;70,71,68,67;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;90,85,96,97;,
 4;85,82,98,96;,
 4;97,96,99,100;,
 4;96,98,101,99;,
 4;102,103,86,93;,
 4;103,104,83,86;,
 4;105,106,103,102;,
 4;106,107,104,103;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;114,115,116,117;,
 4;115,118,119,116;,
 4;120,121,122,123;,
 4;121,124,125,122;,
 4;126,127,128,129;,
 4;127,130,131,128;,
 4;126,121,132,133;,
 4;121,118,134,132;,
 4;133,132,135,136;,
 4;132,134,137,135;,
 4;138,139,122,129;,
 4;139,140,119,122;,
 4;141,142,139,138;,
 4;142,143,140,139;,
 4;144,145,146,147;,
 4;145,148,149,146;,
 4;150,151,152,153;,
 4;151,154,155,152;,
 4;156,157,158,159;,
 4;157,160,161,158;,
 4;162,163,164,165;,
 4;163,166,167,164;,
 4;162,157,168,169;,
 4;157,154,170,168;,
 4;169,168,171,172;,
 4;168,170,173,171;,
 4;174,175,158,165;,
 4;175,176,155,158;,
 4;177,178,175,174;,
 4;178,179,176,175;,
 4;180,181,182,183;,
 4;181,184,185,182;,
 4;186,187,188,189;,
 4;187,190,191,188;,
 4;192,193,194,195;,
 4;193,196,197,194;,
 4;198,199,200,201;,
 4;199,202,203,200;,
 4;198,193,204,205;,
 4;193,190,206,204;,
 4;205,204,207,208;,
 4;204,206,209,207;,
 4;210,211,194,201;,
 4;211,212,191,194;,
 4;213,214,211,210;,
 4;214,215,212,211;,
 4;216,217,218,219;,
 4;217,220,221,218;,
 4;222,223,224,225;,
 4;223,226,227,224;,
 4;228,229,230,231;,
 4;229,232,233,230;,
 4;234,235,236,237;,
 4;235,238,239,236;,
 4;234,229,240,241;,
 4;229,226,242,240;,
 4;241,240,243,244;,
 4;240,242,245,243;,
 4;246,247,230,237;,
 4;247,248,227,230;,
 4;249,250,247,246;,
 4;250,251,248,247;,
 4;252,253,254,255;,
 4;253,256,257,254;,
 4;258,259,260,261;,
 4;259,262,263,260;,
 4;264,265,266,267;,
 4;265,268,269,266;,
 4;270,271,272,273;,
 4;271,274,275,272;,
 4;270,265,276,277;,
 4;265,262,278,276;,
 4;277,276,279,280;,
 4;276,278,281,279;,
 4;282,283,266,273;,
 4;283,284,263,266;,
 4;285,286,283,282;,
 4;286,287,284,283;,
 4;288,289,290,291;,
 4;289,292,293,290;,
 4;294,295,296,297;,
 4;295,298,299,296;,
 4;300,301,302,303;,
 4;301,304,305,302;,
 4;306,307,308,309;,
 4;307,310,311,308;,
 4;306,301,312,313;,
 4;301,298,314,312;,
 4;313,312,315,316;,
 4;312,314,317,315;,
 4;318,319,302,309;,
 4;319,320,299,302;,
 4;321,322,319,318;,
 4;322,323,320,319;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;336,337,338,339;,
 4;336,329,340,341;,
 4;342,343,330,339;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;356,349,360,361;,
 4;362,363,350,359;;
 
 MeshMaterialList {
  3;
  156;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.188000;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.483200;0.483200;0.483200;1.000000;;
   6.000000;
   0.780000;0.780000;0.780000;;
   0.066440;0.066440;0.066440;;
  }
  Material {
   0.793600;0.721600;0.163200;1.000000;;
   5.000000;
   0.330000;0.330000;0.330000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  198;
  -0.711019;0.388911;0.585833;,
  -0.999850;0.009575;0.014423;,
  -0.704752;-0.392385;-0.591065;,
  0.003572;-0.553077;-0.833122;,
  0.699797;-0.395089;-0.595138;,
  0.999998;-0.001166;-0.001756;,
  0.714994;0.386676;0.582465;,
  -0.003218;0.553078;0.833123;,
  -0.000000;0.906308;-0.422617;,
  -0.000000;-0.906308;0.422618;,
  0.000004;0.906311;-0.422611;,
  0.000003;0.906308;-0.422617;,
  -0.000000;0.906311;-0.422611;,
  0.000002;0.906305;-0.422623;,
  0.000000;0.906305;-0.422623;,
  -0.000003;0.906308;-0.422617;,
  -0.000004;0.906311;-0.422611;,
  -0.000001;0.906305;-0.422623;,
  0.000000;-0.906311;0.422612;,
  -0.000002;-0.906308;0.422618;,
  -0.000003;-0.906311;0.422612;,
  -0.000000;-0.906305;0.422624;,
  -0.000002;-0.906305;0.422624;,
  0.000003;-0.906311;0.422612;,
  0.000002;-0.906308;0.422618;,
  0.000001;-0.906305;0.422624;,
  0.456360;-0.678007;0.576231;,
  -0.143126;-0.959161;0.243976;,
  -0.684883;-0.685284;-0.247631;,
  -0.810956;-0.006148;-0.585074;,
  -0.467394;0.666991;-0.580229;,
  0.155387;0.959446;-0.235199;,
  0.677944;0.695169;0.239024;,
  0.811016;0.006504;0.584988;,
  -0.562805;0.281654;0.777124;,
  0.562804;-0.281662;-0.777122;,
  -0.562808;0.281640;0.777127;,
  -0.562806;0.281634;0.777131;,
  -0.562806;0.281657;0.777122;,
  -0.562804;0.281628;0.777134;,
  -0.562804;0.281651;0.777126;,
  -0.562804;0.281674;0.777117;,
  -0.562805;0.281673;0.777117;,
  -0.562804;0.281674;0.777117;,
  0.562812;-0.281660;-0.777117;,
  0.562807;-0.281657;-0.777122;,
  0.562816;-0.281642;-0.777120;,
  0.562796;-0.281664;-0.777127;,
  0.562797;-0.281672;-0.777123;,
  0.562808;-0.281678;-0.777113;,
  0.562801;-0.281668;-0.777122;,
  0.562794;-0.281657;-0.777130;,
  0.180653;0.701085;0.689815;,
  0.233682;0.972178;0.016225;,
  0.154765;0.696863;-0.700307;,
  -0.018651;-0.003166;-0.999821;,
  -0.178115;-0.689609;-0.701936;,
  -0.233464;-0.972364;-0.001583;,
  -0.157517;-0.707478;0.688959;,
  0.018529;0.002660;0.999825;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.713666;0.296038;0.634856;,
  -0.999853;0.007253;0.015554;,
  -0.707156;-0.298815;-0.640811;,
  0.003603;-0.422616;-0.906302;,
  0.702306;-0.300852;-0.645178;,
  0.999998;-0.000884;-0.001895;,
  0.717554;0.294355;0.631246;,
  -0.003246;0.422616;0.906303;,
  0.000000;0.906308;-0.422619;,
  -0.000000;-0.906308;0.422618;,
  -0.713670;-0.296037;0.634853;,
  -0.999853;-0.007253;0.015554;,
  -0.707161;0.298813;-0.640807;,
  0.003604;0.422616;-0.906302;,
  0.702305;0.300852;-0.645179;,
  0.999998;0.000884;-0.001895;,
  0.717554;-0.294355;0.631246;,
  -0.003245;-0.422616;0.906303;,
  -0.000000;0.906308;0.422619;,
  -0.000000;-0.906308;-0.422618;,
  0.000001;0.906310;-0.422614;,
  0.000001;0.906308;-0.422619;,
  -0.000000;0.906310;-0.422614;,
  0.000002;0.906305;-0.422623;,
  0.000000;0.906305;-0.422623;,
  -0.000001;0.906308;-0.422619;,
  -0.000001;0.906310;-0.422614;,
  -0.000001;0.906305;-0.422623;,
  -0.000000;-0.906310;0.422613;,
  -0.000002;-0.906308;0.422618;,
  -0.000003;-0.906311;0.422612;,
  -0.000000;-0.906305;0.422624;,
  -0.000001;-0.906305;0.422624;,
  0.000002;-0.906310;0.422613;,
  0.000002;-0.906308;0.422618;,
  0.000001;-0.906305;0.422624;,
  0.000001;0.906306;0.422623;,
  0.000001;0.906308;0.422619;,
  -0.000000;0.906306;0.422623;,
  0.000000;0.906309;0.422615;,
  0.000000;0.906309;0.422615;,
  -0.000001;0.906308;0.422619;,
  -0.000001;0.906305;0.422623;,
  -0.000000;0.906309;0.422615;,
  -0.000000;-0.906310;-0.422614;,
  0.000002;-0.906308;-0.422618;,
  0.000002;-0.906310;-0.422614;,
  0.000000;-0.906306;-0.422623;,
  0.000002;-0.906306;-0.422623;,
  -0.000002;-0.906310;-0.422614;,
  -0.000002;-0.906308;-0.422618;,
  -0.000002;-0.906306;-0.422623;,
  0.712699;0.068625;0.698105;,
  0.995252;0.095832;0.017029;,
  0.706014;0.067981;-0.704927;,
  -0.003615;-0.000348;-0.999993;,
  -0.701281;-0.067526;-0.709680;,
  -0.995394;-0.095846;-0.002074;,
  -0.716496;-0.068991;0.694171;,
  0.003255;0.000313;0.999995;,
  0.095856;-0.995395;0.000003;,
  -0.095850;0.995396;-0.000005;,
  0.095838;-0.995397;0.000010;,
  0.095842;-0.995397;0.000004;,
  0.095855;-0.995395;0.000019;,
  0.095846;-0.995396;-0.000001;,
  0.095857;-0.995395;-0.000013;,
  0.095869;-0.995394;0.000002;,
  0.095872;-0.995394;0.000029;,
  0.095867;-0.995394;-0.000025;,
  -0.095857;0.995395;0.000006;,
  -0.095870;0.995394;0.000003;,
  -0.095873;0.995394;0.000027;,
  -0.095842;0.995397;-0.000015;,
  -0.095867;0.995394;-0.000022;,
  -0.095841;0.995397;-0.000015;,
  -0.095830;0.995398;-0.000012;,
  -0.095818;0.995399;-0.000009;,
  0.716001;0.000000;0.698099;,
  0.999855;-0.000000;0.017031;,
  0.709287;-0.000000;-0.704920;,
  -0.003636;-0.000000;-0.999993;,
  -0.704525;0.000000;-0.709679;,
  -0.999998;0.000000;-0.002067;,
  -0.719808;0.000000;0.694173;,
  0.003263;0.000000;0.999995;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.728510;-0.010083;0.684961;,
  0.999768;-0.014034;0.016328;,
  0.720666;-0.009996;-0.693210;,
  -0.003836;-0.000133;-0.999993;,
  -0.716504;0.008501;-0.697531;,
  -0.999930;0.011669;-0.001986;,
  -0.732022;0.008687;0.681226;,
  0.003350;-0.000254;0.999994;,
  -0.453984;-0.891010;0.000001;,
  0.000000;1.000000;0.000000;,
  -0.454001;-0.891001;0.000003;,
  -0.453997;-0.891003;0.000004;,
  -0.453987;-0.891008;0.000002;,
  -0.453994;-0.891005;0.000005;,
  -0.453981;-0.891011;0.000000;,
  -0.453971;-0.891017;-0.000002;,
  -0.453972;-0.891016;0.000001;,
  -0.453969;-0.891017;-0.000004;,
  0.730763;0.018640;0.682377;,
  0.999550;0.025252;0.016193;,
  0.722709;0.018407;-0.690907;,
  -0.003884;-0.000334;-0.999992;,
  -0.718609;-0.020102;-0.695124;,
  -0.999600;-0.028209;-0.001969;,
  -0.734166;-0.020535;0.678659;,
  0.003356;-0.000177;0.999994;,
  -0.468473;-0.883478;0.000008;,
  0.000000;1.000000;0.000000;,
  -0.468473;-0.883478;0.000020;,
  -0.468461;-0.883484;0.000013;,
  -0.468478;-0.883475;0.000015;,
  -0.468450;-0.883490;0.000007;,
  -0.468469;-0.883480;-0.000000;,
  -0.468486;-0.883471;0.000002;,
  -0.468484;-0.883472;0.000011;,
  -0.468487;-0.883470;-0.000007;,
  -0.430507;0.902587;0.000000;,
  -0.000000;-0.000000;-1.000000;,
  0.430507;-0.902587;-0.000000;,
  0.000000;-0.000000;1.000000;,
  0.902585;0.430512;0.000000;,
  -0.902585;-0.430512;0.000000;,
  -0.891009;0.453985;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.891009;-0.453985;-0.000000;,
  0.000000;-0.000000;1.000000;,
  0.453991;0.891006;-0.000000;,
  -0.453991;-0.891006;0.000000;;
  156;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,0,0,7;,
  4;10,11,8,12;,
  4;11,13,14,8;,
  4;12,8,15,16;,
  4;8,14,17,15;,
  4;18,9,19,20;,
  4;9,21,22,19;,
  4;23,24,9,18;,
  4;24,25,21,9;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,26,26,33;,
  4;36,37,34,38;,
  4;37,39,40,34;,
  4;38,34,41,42;,
  4;34,40,43,41;,
  4;44,35,45,46;,
  4;35,47,48,45;,
  4;49,50,35,44;,
  4;50,51,47,35;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,52,52,59;,
  4;60,60,60,60;,
  4;60,60,60,60;,
  4;60,60,60,60;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;61,61,61,61;,
  4;61,61,61,61;,
  4;61,61,61,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;68,69,69,68;,
  4;69,62,62,69;,
  4;82,83,70,84;,
  4;83,85,86,70;,
  4;84,70,87,88;,
  4;70,86,89,87;,
  4;90,71,91,92;,
  4;71,93,94,91;,
  4;95,96,71,90;,
  4;96,97,93,71;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,72,72,79;,
  4;98,99,80,100;,
  4;99,101,102,80;,
  4;100,80,103,104;,
  4;80,102,105,103;,
  4;106,81,107,108;,
  4;81,109,110,107;,
  4;111,112,81,106;,
  4;112,113,109,81;,
  4;114,115,115,114;,
  4;115,116,116,115;,
  4;116,117,117,116;,
  4;117,118,118,117;,
  4;118,119,119,118;,
  4;119,120,120,119;,
  4;120,121,121,120;,
  4;121,114,114,121;,
  4;124,125,122,126;,
  4;125,127,128,122;,
  4;126,122,129,130;,
  4;122,128,131,129;,
  4;132,123,133,134;,
  4;123,135,136,133;,
  4;137,138,123,132;,
  4;138,139,135,123;,
  4;140,141,141,140;,
  4;141,142,142,141;,
  4;142,143,143,142;,
  4;143,144,144,143;,
  4;144,145,145,144;,
  4;145,146,146,145;,
  4;146,147,147,146;,
  4;147,140,140,147;,
  4;148,148,148,148;,
  4;148,148,148,148;,
  4;148,148,148,148;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;149,149,149,149;,
  4;149,149,149,149;,
  4;149,149,149,149;,
  4;150,151,151,150;,
  4;151,152,152,151;,
  4;152,153,153,152;,
  4;153,154,154,153;,
  4;154,155,155,154;,
  4;155,156,156,155;,
  4;156,157,157,156;,
  4;157,150,150,157;,
  4;160,161,158,162;,
  4;161,163,164,158;,
  4;162,158,165,166;,
  4;158,164,167,165;,
  4;159,159,159,159;,
  4;159,159,159,159;,
  4;159,159,159,159;,
  4;159,159,159,159;,
  4;168,169,169,168;,
  4;169,170,170,169;,
  4;170,171,171,170;,
  4;171,172,172,171;,
  4;172,173,173,172;,
  4;173,174,174,173;,
  4;174,175,175,174;,
  4;175,168,168,175;,
  4;178,179,176,180;,
  4;179,181,182,176;,
  4;180,176,183,184;,
  4;176,182,185,183;,
  4;177,177,177,177;,
  4;177,177,177,177;,
  4;177,177,177,177;,
  4;177,177,177,177;,
  4;186,186,186,186;,
  4;187,187,187,187;,
  4;188,188,188,188;,
  4;189,189,189,189;,
  4;190,190,190,190;,
  4;191,191,191,191;,
  4;192,192,192,192;,
  4;193,193,193,193;,
  4;194,194,194,194;,
  4;195,195,195,195;,
  4;196,196,196,196;,
  4;197,197,197,197;;
 }
 MeshTextureCoords {
  364;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
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