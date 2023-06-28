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
 291;
 -28.21635;31.34298;5.82243;,
 -25.57464;32.98488;3.93519;,
 20.83980;3.87075;43.57689;,
 18.19809;2.22888;45.46410;,
 -24.38364;36.26859;4.95240;,
 22.03083;7.15443;44.59410;,
 -25.83435;37.91043;7.85682;,
 20.58009;8.79636;47.49852;,
 -28.47609;36.26859;9.74406;,
 17.93838;7.15443;49.38576;,
 -29.66709;32.98488;8.72685;,
 16.74735;3.87075;48.36855;,
 -28.21635;31.34298;5.82243;,
 18.19809;2.22888;45.46410;,
 -27.02535;34.62672;6.83964;,
 -27.02535;34.62672;6.83964;,
 -27.02535;34.62672;6.83964;,
 -27.02535;34.62672;6.83964;,
 -27.02535;34.62672;6.83964;,
 -27.02535;34.62672;6.83964;,
 19.38909;5.51262;46.48131;,
 19.38909;5.51262;46.48131;,
 19.38909;5.51262;46.48131;,
 19.38909;5.51262;46.48131;,
 19.38909;5.51262;46.48131;,
 19.38909;5.51262;46.48131;,
 -17.12733;35.50182;24.47637;,
 -14.71374;38.14422;25.13073;,
 33.64518;1.31196;-4.50366;,
 31.23159;-1.33044;-5.15805;,
 -12.81282;38.14422;28.23273;,
 35.54604;1.31196;-1.40166;,
 -13.32552;35.50182;30.68034;,
 35.03340;-1.33044;1.04598;,
 -15.73908;32.85936;30.02589;,
 32.61987;-3.97284;0.39153;,
 -17.64000;32.85936;26.92392;,
 30.71895;-3.97284;-2.71047;,
 -17.12733;35.50182;24.47637;,
 31.23159;-1.33044;-5.15805;,
 -15.22644;35.50182;27.57834;,
 -15.22644;35.50182;27.57834;,
 -15.22644;35.50182;27.57834;,
 -15.22644;35.50182;27.57834;,
 -15.22644;35.50182;27.57834;,
 -15.22644;35.50182;27.57834;,
 33.13248;-1.33044;-2.05605;,
 33.13248;-1.33044;-2.05605;,
 33.13248;-1.33044;-2.05605;,
 33.13248;-1.33044;-2.05605;,
 33.13248;-1.33044;-2.05605;,
 33.13248;-1.33044;-2.05605;,
 24.89748;44.41107;31.77882;,
 28.17255;42.91194;31.26645;,
 2.87025;4.60764;-18.39210;,
 -0.40482;6.10677;-17.87973;,
 29.10807;39.91371;33.10248;,
 3.80580;1.60938;-16.55601;,
 26.76852;38.41449;35.45088;,
 1.46622;0.11025;-14.20764;,
 23.49348;39.91371;35.96325;,
 -1.80882;1.60938;-13.69524;,
 22.55796;42.91194;34.12722;,
 -2.74434;4.60764;-15.53133;,
 24.89748;44.41107;31.77882;,
 -0.40482;6.10677;-17.87973;,
 25.83300;41.41281;33.61485;,
 25.83300;41.41281;33.61485;,
 25.83300;41.41281;33.61485;,
 25.83300;41.41281;33.61485;,
 25.83300;41.41281;33.61485;,
 25.83300;41.41281;33.61485;,
 0.53070;3.10851;-16.04367;,
 0.53070;3.10851;-16.04367;,
 0.53070;3.10851;-16.04367;,
 0.53070;3.10851;-16.04367;,
 0.53070;3.10851;-16.04367;,
 0.53070;3.10851;-16.04367;,
 -14.78784;61.91757;8.36952;,
 -11.63712;61.04958;9.96813;,
 -11.63712;1.61793;-22.30062;,
 -14.78784;2.48592;-23.89923;,
 -11.63712;59.31363;13.16535;,
 -11.63712;-0.11802;-19.10340;,
 -14.78784;58.44564;14.76399;,
 -14.78784;-0.98601;-17.50476;,
 -17.93853;59.31363;13.16535;,
 -17.93853;-0.11802;-19.10340;,
 -17.93853;61.04958;9.96813;,
 -17.93853;1.61793;-22.30062;,
 -14.78784;61.91757;8.36952;,
 -14.78784;2.48592;-23.89923;,
 -14.78784;60.18162;11.56671;,
 -14.78784;60.18162;11.56671;,
 -14.78784;60.18162;11.56671;,
 -14.78784;60.18162;11.56671;,
 -14.78784;60.18162;11.56671;,
 -14.78784;60.18162;11.56671;,
 -14.78784;0.74997;-20.70201;,
 -14.78784;0.74997;-20.70201;,
 -14.78784;0.74997;-20.70201;,
 -14.78784;0.74997;-20.70201;,
 -14.78784;0.74997;-20.70201;,
 -14.78784;0.74997;-20.70201;,
 -5.78889;35.77101;-3.75876;,
 -3.48657;34.30563;-1.35285;,
 -54.06225;-2.15856;24.83595;,
 -56.36451;-0.69324;22.43007;,
 -2.96745;35.90334;1.87419;,
 -53.54313;-0.56091;28.06302;,
 -4.75065;38.96631;2.69535;,
 -55.32630;2.50209;28.88418;,
 -7.05291;40.43166;0.28947;,
 -57.62859;3.96741;26.47827;,
 -7.57203;38.83398;-2.93760;,
 -58.14771;2.36973;23.25123;,
 -5.78889;35.77101;-3.75876;,
 -56.36451;-0.69324;22.43007;,
 -5.26977;37.36863;-0.53169;,
 -5.26977;37.36863;-0.53169;,
 -5.26977;37.36863;-0.53169;,
 -5.26977;37.36863;-0.53169;,
 -5.26977;37.36863;-0.53169;,
 -5.26977;37.36863;-0.53169;,
 -55.84539;0.90441;25.65711;,
 -55.84539;0.90441;25.65711;,
 -55.84539;0.90441;25.65711;,
 -55.84539;0.90441;25.65711;,
 -55.84539;0.90441;25.65711;,
 -55.84539;0.90441;25.65711;,
 15.45159;38.95086;9.69528;,
 16.85787;41.23275;12.15519;,
 -8.90631;3.42465;61.95630;,
 -10.31259;1.14276;59.49639;,
 14.91474;44.08215;13.31316;,
 -10.84944;6.27408;63.11424;,
 11.56527;44.64972;12.01119;,
 -14.19888;6.84162;61.81233;,
 10.15899;42.36780;9.55128;,
 -15.60519;4.55967;59.35236;,
 12.10215;39.51837;8.39331;,
 -13.66203;1.71027;58.19442;,
 15.45159;38.95086;9.69528;,
 -10.31259;1.14276;59.49639;,
 13.50846;41.80029;10.85325;,
 13.50846;41.80029;10.85325;,
 13.50846;41.80029;10.85325;,
 13.50846;41.80029;10.85325;,
 13.50846;41.80029;10.85325;,
 13.50846;41.80029;10.85325;,
 -12.25572;3.99216;60.65433;,
 -12.25572;3.99216;60.65433;,
 -12.25572;3.99216;60.65433;,
 -12.25572;3.99216;60.65433;,
 -12.25572;3.99216;60.65433;,
 -12.25572;3.99216;60.65433;,
 -7.74849;80.95929;-13.08426;,
 1.05894;60.61323;53.51346;,
 46.04910;69.18222;0.32286;,
 1.05894;60.61323;53.51346;,
 65.65758;35.81433;41.73213;,
 1.05894;60.61323;53.51346;,
 36.31134;5.98245;79.96131;,
 1.05894;60.61323;53.51346;,
 -19.89123;2.15049;86.22322;,
 1.05894;60.61323;53.51346;,
 -60.62841;27.20385;55.80267;,
 1.05894;60.61323;53.51346;,
 -55.22436;62.27706;11.60661;,
 1.05894;60.61323;53.51346;,
 -7.74849;80.95929;-13.08426;,
 0.64650;40.50990;37.50930;,
 -7.74849;80.95929;-13.08426;,
 46.04910;69.18222;0.32286;,
 65.65758;35.81433;41.73213;,
 36.31134;5.98245;79.96131;,
 -19.89123;2.15049;86.22322;,
 -60.62841;27.20385;55.80267;,
 -55.22436;62.27706;11.60661;,
 0.69297;66.15840;53.62197;,
 5.47155;64.85844;55.13166;,
 5.41764;62.23089;53.03985;,
 0.63906;63.53082;51.53013;,
 6.13695;61.65228;59.14188;,
 6.08304;59.02473;57.05010;,
 2.02377;59.74602;61.64238;,
 1.96989;57.11850;59.55060;,
 -2.75481;61.04604;60.13263;,
 -2.80872;58.41843;58.04079;,
 -3.42021;64.25220;56.12241;,
 -3.47412;61.62459;54.03057;,
 0.69297;66.15840;53.62197;,
 0.63906;63.53082;51.53013;,
 1.35837;62.95227;57.63216;,
 1.35837;62.95227;57.63216;,
 1.35837;62.95227;57.63216;,
 1.35837;62.95227;57.63216;,
 1.35837;62.95227;57.63216;,
 1.35837;62.95227;57.63216;,
 1.30446;60.32466;55.54032;,
 1.30446;60.32466;55.54032;,
 1.30446;60.32466;55.54032;,
 1.30446;60.32466;55.54032;,
 1.30446;60.32466;55.54032;,
 1.30446;60.32466;55.54032;,
 0.09063;65.94882;48.08772;,
 8.48643;63.66483;50.74032;,
 8.42976;60.90291;48.54153;,
 0.03396;63.18687;45.88896;,
 9.65556;58.03173;57.78612;,
 9.59889;55.26981;55.58736;,
 2.42886;54.68256;62.17932;,
 2.37219;51.92061;59.98053;,
 -5.96694;56.96655;59.52678;,
 -6.02361;54.20460;57.32799;,
 -7.13607;62.59968;52.48095;,
 -7.19274;59.83770;50.28216;,
 0.09063;65.94882;48.08772;,
 0.03396;63.18687;45.88896;,
 1.25973;60.31578;55.13355;,
 1.25973;60.31578;55.13355;,
 1.25973;60.31578;55.13355;,
 1.25973;60.31578;55.13355;,
 1.25973;60.31578;55.13355;,
 1.25973;60.31578;55.13355;,
 1.20309;57.55374;52.93473;,
 1.20309;57.55374;52.93473;,
 1.20309;57.55374;52.93473;,
 1.20309;57.55374;52.93473;,
 1.20309;57.55374;52.93473;,
 1.20309;57.55374;52.93473;,
 1.74051;43.05339;4.31007;,
 24.85311;2.37918;-9.07866;,
 6.32226;-2.03346;-27.66240;,
 -16.79028;38.64072;-14.27370;,
 24.85311;2.37918;-9.07866;,
 23.15931;0.73203;-6.99858;,
 4.62849;-3.68061;-25.58235;,
 6.32226;-2.03346;-27.66240;,
 23.15931;0.73203;-6.99858;,
 0.04674;41.40624;6.39018;,
 -18.48408;36.99357;-12.19359;,
 4.62849;-3.68061;-25.58235;,
 0.04674;41.40624;6.39018;,
 1.74051;43.05339;4.31007;,
 -16.79028;38.64072;-14.27370;,
 -18.48408;36.99357;-12.19359;,
 24.85311;2.37918;-9.07866;,
 1.74051;43.05339;4.31007;,
 -16.79028;38.64072;-14.27370;,
 6.32226;-2.03346;-27.66240;,
 -11.38488;39.16338;40.63995;,
 -56.37123;22.62825;32.23368;,
 -50.75019;0.43656;45.80394;,
 -5.76393;16.97172;54.21021;,
 -56.37123;22.62825;32.23368;,
 -55.37229;21.25914;29.58099;,
 -49.75131;-0.93252;43.15131;,
 -50.75019;0.43656;45.80394;,
 -55.37229;21.25914;29.58099;,
 -10.38597;37.79430;37.98732;,
 -4.76499;15.60261;51.55755;,
 -49.75131;-0.93252;43.15131;,
 -10.38597;37.79430;37.98732;,
 -11.38488;39.16338;40.63995;,
 -5.76393;16.97172;54.21021;,
 -4.76499;15.60261;51.55755;,
 -56.37123;22.62825;32.23368;,
 -11.38488;39.16338;40.63995;,
 -5.76393;16.97172;54.21021;,
 -50.75019;0.43656;45.80394;,
 -11.56749;3.31212;45.80796;,
 -40.92090;1.15902;7.05780;,
 -19.70349;0.98286;-9.00480;,
 9.64989;3.13593;29.74551;,
 -40.92090;1.15902;7.05780;,
 -40.98837;4.30374;6.93417;,
 -19.77087;4.12761;-9.12849;,
 -19.70349;0.98286;-9.00480;,
 -40.98837;4.30374;6.93417;,
 -11.63499;6.45678;45.68430;,
 9.58239;6.28056;29.62179;,
 -19.77087;4.12761;-9.12849;,
 -11.63499;6.45678;45.68430;,
 -11.56749;3.31212;45.80796;,
 9.64989;3.13593;29.74551;,
 9.58239;6.28056;29.62179;,
 -40.92090;1.15902;7.05780;,
 -11.56749;3.31212;45.80796;,
 9.64989;3.13593;29.74551;,
 -19.70349;0.98286;-9.00480;;
 
 176;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 3;14,1,0;,
 3;15,4,1;,
 3;16,6,4;,
 3;17,8,6;,
 3;18,10,8;,
 3;19,12,10;,
 3;20,3,2;,
 3;21,2,5;,
 3;22,5,7;,
 3;23,7,9;,
 3;24,9,11;,
 3;25,11,13;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 3;40,27,26;,
 3;41,30,27;,
 3;42,32,30;,
 3;43,34,32;,
 3;44,36,34;,
 3;45,38,36;,
 3;46,29,28;,
 3;47,28,31;,
 3;48,31,33;,
 3;49,33,35;,
 3;50,35,37;,
 3;51,37,39;,
 4;52,53,54,55;,
 4;53,56,57,54;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 3;66,53,52;,
 3;67,56,53;,
 3;68,58,56;,
 3;69,60,58;,
 3;70,62,60;,
 3;71,64,62;,
 3;72,55,54;,
 3;73,54,57;,
 3;74,57,59;,
 3;75,59,61;,
 3;76,61,63;,
 3;77,63,65;,
 4;78,79,80,81;,
 4;79,82,83,80;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 4;88,90,91,89;,
 3;92,79,78;,
 3;93,82,79;,
 3;94,84,82;,
 3;95,86,84;,
 3;96,88,86;,
 3;97,90,88;,
 3;98,81,80;,
 3;99,80,83;,
 3;100,83,85;,
 3;101,85,87;,
 3;102,87,89;,
 3;103,89,91;,
 4;104,105,106,107;,
 4;105,108,109,106;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 3;118,105,104;,
 3;119,108,105;,
 3;120,110,108;,
 3;121,112,110;,
 3;122,114,112;,
 3;123,116,114;,
 3;124,107,106;,
 3;125,106,109;,
 3;126,109,111;,
 3;127,111,113;,
 3;128,113,115;,
 3;129,115,117;,
 4;130,131,132,133;,
 4;131,134,135,132;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 3;144,131,130;,
 3;145,134,131;,
 3;146,136,134;,
 3;147,138,136;,
 3;148,140,138;,
 3;149,142,140;,
 3;150,133,132;,
 3;151,132,135;,
 3;152,135,137;,
 3;153,137,139;,
 3;154,139,141;,
 3;155,141,143;,
 3;156,157,158;,
 3;158,159,160;,
 3;160,161,162;,
 3;162,163,164;,
 3;164,165,166;,
 3;166,167,168;,
 3;168,169,170;,
 3;171,172,173;,
 3;171,173,174;,
 3;171,174,175;,
 3;171,175,176;,
 3;171,176,177;,
 3;171,177,178;,
 3;171,178,172;,
 4;179,180,181,182;,
 4;180,183,184,181;,
 4;183,185,186,184;,
 4;185,187,188,186;,
 4;187,189,190,188;,
 4;189,191,192,190;,
 3;193,180,179;,
 3;194,183,180;,
 3;195,185,183;,
 3;196,187,185;,
 3;197,189,187;,
 3;198,191,189;,
 3;199,182,181;,
 3;200,181,184;,
 3;201,184,186;,
 3;202,186,188;,
 3;203,188,190;,
 3;204,190,192;,
 4;205,206,207,208;,
 4;206,209,210,207;,
 4;209,211,212,210;,
 4;211,213,214,212;,
 4;213,215,216,214;,
 4;215,217,218,216;,
 3;219,206,205;,
 3;220,209,206;,
 3;221,211,209;,
 3;222,213,211;,
 3;223,215,213;,
 3;224,217,215;,
 3;225,208,207;,
 3;226,207,210;,
 3;227,210,212;,
 3;228,212,214;,
 3;229,214,216;,
 3;230,216,218;,
 4;231,232,233,234;,
 4;235,236,237,238;,
 4;239,240,241,242;,
 4;243,244,245,246;,
 4;243,236,247,248;,
 4;249,250,237,246;,
 4;251,252,253,254;,
 4;255,256,257,258;,
 4;259,260,261,262;,
 4;263,264,265,266;,
 4;263,256,267,268;,
 4;269,270,257,266;,
 4;271,272,273,274;,
 4;275,276,277,278;,
 4;279,280,281,282;,
 4;283,284,285,286;,
 4;283,276,287,288;,
 4;289,290,277,286;;
 
 MeshMaterialList {
  3;
  176;
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
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "TEXTURE\\N845_mokumetex_TP_V4.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "TEXTURE\\G142_mokumecyou_TP_V4.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  194;
  -0.686332;0.430513;-0.586181;,
  0.041223;-0.781660;-0.622341;,
  0.649447;-0.000002;-0.760407;,
  0.608231;0.781659;-0.138072;,
  -0.041220;0.781661;0.622340;,
  -0.649447;0.000002;0.760407;,
  0.686330;-0.430516;0.586179;,
  -0.608230;-0.781660;0.138069;,
  -0.686337;0.430514;-0.586173;,
  -0.686332;0.430512;-0.586181;,
  -0.686336;0.430513;-0.586175;,
  -0.686332;0.430511;-0.586181;,
  -0.686327;0.430513;-0.586185;,
  -0.686326;0.430513;-0.586187;,
  0.686332;-0.430512;0.586181;,
  0.686328;-0.430518;0.586182;,
  0.686323;-0.430518;0.586187;,
  0.686332;-0.430512;0.586181;,
  0.686337;-0.430518;0.586171;,
  0.686332;-0.430518;0.586176;,
  -0.715086;0.544633;0.438208;,
  -0.220310;0.419332;-0.880695;,
  0.464383;0.838670;-0.284571;,
  0.684688;0.419337;0.596119;,
  0.220302;-0.419340;0.880693;,
  -0.464379;-0.838671;0.284575;,
  0.715089;-0.544633;-0.438204;,
  -0.684686;-0.419330;-0.596126;,
  -0.715080;0.544646;0.438203;,
  -0.715087;0.544634;0.438206;,
  -0.715079;0.544646;0.438204;,
  -0.715087;0.544633;0.438208;,
  -0.715093;0.544620;0.438214;,
  -0.715092;0.544622;0.438212;,
  0.715088;-0.544636;-0.438202;,
  0.715086;-0.544642;-0.438198;,
  0.715087;-0.544639;-0.438200;,
  0.715090;-0.544630;-0.438206;,
  0.715092;-0.544624;-0.438210;,
  0.715091;-0.544627;-0.438208;,
  0.374146;0.566402;0.734305;,
  0.222808;0.713716;-0.664053;,
  0.891006;0.000003;-0.453992;,
  0.668197;-0.713714;0.210062;,
  -0.222815;-0.713712;0.664055;,
  -0.891006;0.000000;0.453991;,
  -0.374143;-0.566409;-0.734301;,
  -0.668197;0.713714;-0.210062;,
  0.374142;0.566406;0.734304;,
  0.374146;0.566404;0.734304;,
  0.374139;0.566402;0.734309;,
  0.374148;0.566396;0.734308;,
  0.374154;0.566402;0.734301;,
  0.374148;0.566406;0.734301;,
  -0.374144;-0.566408;-0.734301;,
  -0.374142;-0.566412;-0.734299;,
  -0.374137;-0.566410;-0.734304;,
  -0.374144;-0.566404;-0.734305;,
  -0.374149;-0.566408;-0.734298;,
  -0.374143;-0.566411;-0.734299;,
  -0.000000;0.878816;0.477160;,
  0.499997;0.413232;-0.761079;,
  1.000000;0.000000;0.000000;,
  0.500003;-0.413231;0.761077;,
  -0.500006;-0.413230;0.761075;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.878816;-0.477160;,
  -0.500001;0.413231;-0.761078;,
  0.000001;0.878816;0.477161;,
  -0.000000;0.878815;0.477163;,
  -0.000000;0.878817;0.477158;,
  0.000000;0.878818;0.477158;,
  0.000000;0.878817;0.477158;,
  -0.000001;0.878816;0.477161;,
  0.000000;-0.878817;-0.477159;,
  -0.000004;-0.878817;-0.477159;,
  -0.000003;-0.878816;-0.477160;,
  0.000000;-0.878815;-0.477162;,
  0.000003;-0.878816;-0.477161;,
  0.000004;-0.878817;-0.477159;,
  0.747863;0.539198;-0.387254;,
  0.200593;-0.739622;-0.642434;,
  0.648336;-0.718620;0.251486;,
  0.447737;0.021009;0.893918;,
  -0.200596;0.739623;0.642432;,
  -0.648337;0.718620;-0.251487;,
  -0.747862;-0.539201;0.387252;,
  -0.447738;-0.021007;-0.893918;,
  0.747859;0.539203;-0.387256;,
  0.747866;0.539201;-0.387246;,
  0.747854;0.539205;-0.387262;,
  0.747861;0.539199;-0.387258;,
  0.747870;0.539190;-0.387253;,
  0.747870;0.539194;-0.387248;,
  -0.747861;-0.539202;0.387254;,
  -0.747866;-0.539197;0.387251;,
  -0.747866;-0.539198;0.387249;,
  -0.747864;-0.539201;0.387249;,
  -0.747859;-0.539204;0.387254;,
  -0.747856;-0.539205;0.387257;,
  0.380977;0.559070;-0.736408;,
  0.839906;-0.542250;0.022852;,
  0.754711;0.272061;0.596987;,
  -0.085187;0.814313;0.574141;,
  -0.839907;0.542248;-0.022853;,
  -0.754707;-0.272066;-0.596990;,
  -0.380976;-0.559069;0.736410;,
  0.085201;-0.814315;-0.574135;,
  0.380978;0.559071;-0.736407;,
  0.380978;0.559069;-0.736409;,
  0.380980;0.559072;-0.736405;,
  0.380978;0.559070;-0.736408;,
  0.380974;0.559070;-0.736410;,
  0.380976;0.559070;-0.736409;,
  -0.380978;-0.559068;0.736409;,
  -0.380980;-0.559066;0.736410;,
  -0.380975;-0.559067;0.736412;,
  -0.380972;-0.559072;0.736410;,
  -0.380974;-0.559071;0.736409;,
  -0.380976;-0.559069;0.736410;,
  -0.032123;0.954676;0.295908;,
  0.269437;0.888660;0.371061;,
  0.379352;0.701618;0.603178;,
  0.214853;0.534395;0.817472;,
  -0.100189;0.512915;0.852573;,
  -0.328540;0.653353;0.682050;,
  -0.298248;0.849954;0.434311;,
  0.016049;0.782257;0.622750;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  -0.016049;-0.782257;-0.622749;,
  0.016055;0.782255;0.622752;,
  0.384474;0.570121;-0.726045;,
  0.991577;0.067606;-0.110477;,
  0.607102;-0.502503;0.615564;,
  -0.384486;-0.570117;0.726042;,
  -0.991577;-0.067607;0.110477;,
  -0.016046;-0.782258;-0.622748;,
  0.016051;0.782256;0.622750;,
  0.384481;0.570116;-0.726046;,
  0.991576;0.067609;-0.110481;,
  0.607094;-0.502508;0.615566;,
  -0.384479;-0.570117;0.726046;,
  -0.991576;-0.067609;0.110481;,
  -0.016048;-0.782256;-0.622751;,
  -0.607092;0.502511;-0.615566;,
  0.016061;0.782258;0.622748;,
  0.016055;0.782258;0.622748;,
  0.016058;0.782253;0.622754;,
  0.016056;0.782249;0.622759;,
  0.016052;0.782253;0.622754;,
  0.016048;0.782257;0.622749;,
  -0.016048;-0.782255;-0.622752;,
  -0.016047;-0.782257;-0.622749;,
  -0.016045;-0.782260;-0.622745;,
  -0.016044;-0.782261;-0.622744;,
  -0.016045;-0.782259;-0.622747;,
  -0.016046;-0.782256;-0.622751;,
  -0.607095;0.502505;-0.615569;,
  0.016057;0.782260;0.622746;,
  0.016050;0.782261;0.622744;,
  0.016057;0.782254;0.622753;,
  0.016052;0.782249;0.622759;,
  0.016046;0.782253;0.622755;,
  0.016044;0.782259;0.622747;,
  -0.016048;-0.782254;-0.622753;,
  -0.016046;-0.782256;-0.622751;,
  -0.016043;-0.782256;-0.622750;,
  -0.016048;-0.782255;-0.622751;,
  -0.016053;-0.782257;-0.622749;,
  -0.016050;-0.782256;-0.622750;,
  0.538082;0.523272;-0.660798;,
  0.474973;-0.835880;-0.275144;,
  -0.538081;-0.523273;0.660798;,
  -0.474973;0.835882;0.275141;,
  0.696326;0.165815;0.698309;,
  -0.696324;-0.165814;-0.698311;,
  -0.317332;0.434932;0.842695;,
  -0.924493;-0.339807;-0.172753;,
  0.317332;-0.434933;-0.842695;,
  0.924492;0.339808;0.172759;,
  -0.211216;0.833885;-0.509924;,
  0.211216;-0.833884;0.509926;,
  0.021435;-0.998999;0.039271;,
  -0.603233;-0.044248;-0.796337;,
  -0.021434;0.998999;-0.039269;,
  0.603230;0.044271;0.796338;,
  -0.797279;0.006622;0.603574;,
  0.797282;-0.006645;-0.603571;;
  176;
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;7,7,7,7;,
  3;0,8,9;,
  3;0,10,8;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,9,13;,
  3;6,14,15;,
  3;6,15,16;,
  3;6,16,17;,
  3;6,17,18;,
  3;6,18,19;,
  3;6,19,14;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;27,27,27,27;,
  3;20,28,29;,
  3;20,30,28;,
  3;20,31,30;,
  3;20,32,31;,
  3;20,33,32;,
  3;20,29,33;,
  3;26,34,35;,
  3;26,35,36;,
  3;26,36,37;,
  3;26,37,38;,
  3;26,38,39;,
  3;26,39,34;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;47,47,47,47;,
  3;40,48,49;,
  3;40,50,48;,
  3;40,51,50;,
  3;40,52,51;,
  3;40,53,52;,
  3;40,49,53;,
  3;46,54,55;,
  3;46,55,56;,
  3;46,56,57;,
  3;46,57,58;,
  3;46,58,59;,
  3;46,59,54;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;67,67,67,67;,
  3;60,68,69;,
  3;60,70,68;,
  3;60,71,70;,
  3;60,72,71;,
  3;60,73,72;,
  3;60,69,73;,
  3;66,74,75;,
  3;66,75,76;,
  3;66,76,77;,
  3;66,77,78;,
  3;66,78,79;,
  3;66,79,74;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;87,87,87,87;,
  3;80,88,89;,
  3;80,90,88;,
  3;80,91,90;,
  3;80,92,91;,
  3;80,93,92;,
  3;80,89,93;,
  3;86,94,95;,
  3;86,95,96;,
  3;86,96,97;,
  3;86,97,98;,
  3;86,98,99;,
  3;86,99,94;,
  4;101,101,101,101;,
  4;102,102,102,102;,
  4;103,103,103,103;,
  4;104,104,104,104;,
  4;105,105,105,105;,
  4;107,107,107,107;,
  3;100,108,109;,
  3;100,110,108;,
  3;100,111,110;,
  3;100,112,111;,
  3;100,113,112;,
  3;100,109,113;,
  3;106,114,115;,
  3;106,115,116;,
  3;106,116,117;,
  3;106,117,118;,
  3;106,118,119;,
  3;106,119,114;,
  3;120,127,121;,
  3;121,127,122;,
  3;122,127,123;,
  3;123,127,124;,
  3;124,127,125;,
  3;125,127,126;,
  3;126,127,120;,
  3;128,129,130;,
  3;128,130,131;,
  3;128,131,132;,
  3;128,132,133;,
  3;128,133,134;,
  3;128,134,135;,
  3;128,135,129;,
  4;137,137,137,137;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;140,140,140,140;,
  4;141,141,141,141;,
  4;150,150,150,150;,
  3;136,151,152;,
  3;136,153,151;,
  3;136,154,153;,
  3;136,155,154;,
  3;136,156,155;,
  3;136,152,156;,
  3;142,157,158;,
  3;142,158,159;,
  3;142,159,160;,
  3;142,160,161;,
  3;142,161,162;,
  3;142,162,157;,
  4;144,144,144,144;,
  4;145,145,145,145;,
  4;146,146,146,146;,
  4;147,147,147,147;,
  4;148,148,148,148;,
  4;163,163,163,163;,
  3;143,164,165;,
  3;143,166,164;,
  3;143,167,166;,
  3;143,168,167;,
  3;143,169,168;,
  3;143,165,169;,
  3;149,170,171;,
  3;149,171,172;,
  3;149,172,173;,
  3;149,173,174;,
  3;149,174,175;,
  3;149,175,170;,
  4;176,176,176,176;,
  4;177,177,177,177;,
  4;178,178,178,178;,
  4;179,179,179,179;,
  4;180,180,180,180;,
  4;181,181,181,181;,
  4;182,182,182,182;,
  4;183,183,183,183;,
  4;184,184,184,184;,
  4;185,185,185,185;,
  4;186,186,186,186;,
  4;187,187,187,187;,
  4;188,188,188,188;,
  4;189,189,189,189;,
  4;190,190,190,190;,
  4;191,191,191,191;,
  4;192,192,192,192;,
  4;193,193,193,193;;
 }
 MeshTextureCoords {
  291;
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;1.000000;,
  0.071430;0.000000;,
  0.142860;1.000000;,
  0.142860;0.000000;,
  0.285710;1.000000;,
  0.214290;0.000000;,
  0.428570;1.000000;,
  0.285710;0.000000;,
  0.571430;1.000000;,
  0.357140;0.000000;,
  0.714290;1.000000;,
  0.428570;0.000000;,
  0.857140;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.083330;0.000000;,
  0.250000;0.000000;,
  0.416670;0.000000;,
  0.583330;0.000000;,
  0.750000;0.000000;,
  0.916670;0.000000;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
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
