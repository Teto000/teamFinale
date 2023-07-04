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
 252;
 0.00000;4.16211;-76.61973;,
 54.17838;4.16211;-54.17838;,
 54.17838;0.10254;-54.17838;,
 0.00000;0.10254;-76.61973;,
 76.61973;4.16211;0.00000;,
 76.61973;0.10254;0.00000;,
 54.17838;4.16211;54.17838;,
 54.17838;0.10254;54.17838;,
 0.00000;4.16211;76.61973;,
 0.00000;0.10254;76.61973;,
 -54.17838;4.16211;54.17835;,
 -54.17838;0.10254;54.17835;,
 -76.61973;4.16211;0.00000;,
 -76.61973;0.10254;0.00000;,
 -54.17838;4.16211;-54.17838;,
 -54.17838;0.10254;-54.17838;,
 0.00000;4.16211;-76.61973;,
 0.00000;0.10254;-76.61973;,
 0.00000;4.16211;0.00000;,
 54.17838;4.16211;-54.17838;,
 0.00000;4.16211;-76.61973;,
 76.61973;4.16211;0.00000;,
 54.17838;4.16211;54.17838;,
 0.00000;4.16211;76.61973;,
 -54.17838;4.16211;54.17835;,
 -76.61973;4.16211;0.00000;,
 -54.17838;4.16211;-54.17838;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;0.10254;0.00000;,
 0.00000;21.81816;-64.02687;,
 45.27384;21.81816;-45.27384;,
 45.27384;4.22676;-45.27384;,
 0.00000;4.22676;-64.02687;,
 64.02687;21.81816;0.00000;,
 64.02687;4.22676;0.00000;,
 45.27384;21.81816;45.27384;,
 45.27384;4.22676;45.27384;,
 0.00000;21.81816;64.02687;,
 0.00000;4.22676;64.02687;,
 -45.27384;21.81816;45.27381;,
 -45.27384;4.22676;45.27381;,
 -64.02687;21.81816;0.00000;,
 -64.02687;4.22676;0.00000;,
 -45.27384;21.81816;-45.27381;,
 -45.27384;4.22676;-45.27381;,
 0.00000;4.22676;0.00000;,
 0.00000;4.22676;-64.02687;,
 45.27384;4.22676;-45.27384;,
 64.02687;4.22676;0.00000;,
 45.27384;4.22676;45.27384;,
 0.00000;4.22676;64.02687;,
 -45.27384;4.22676;45.27381;,
 -64.02687;4.22676;0.00000;,
 -45.27384;4.22676;-45.27381;,
 0.00000;21.79863;-64.02687;,
 0.00000;4.20723;-64.02687;,
 45.27384;4.20723;-45.27384;,
 45.27384;21.79863;-45.27384;,
 45.27384;21.79863;-45.27384;,
 45.27384;4.20723;-45.27384;,
 64.02687;4.20723;0.00000;,
 64.02687;21.79863;0.00000;,
 64.02687;21.79863;0.00000;,
 64.02687;4.20723;0.00000;,
 45.27384;4.20723;45.27384;,
 45.27384;21.79863;45.27384;,
 0.00000;4.20723;64.02687;,
 0.00000;21.79863;64.02687;,
 0.00000;21.79863;64.02687;,
 0.00000;4.20723;64.02687;,
 -45.27384;4.20723;45.27381;,
 -45.27384;21.79863;45.27381;,
 -64.02687;4.20723;0.00000;,
 -64.02687;21.79863;0.00000;,
 -64.02687;21.79863;0.00000;,
 -64.02687;4.20723;0.00000;,
 -45.27384;4.20723;-45.27381;,
 -45.27384;21.79863;-45.27381;,
 58.02351;22.60029;0.00000;,
 60.14784;25.54854;0.00000;,
 42.53097;25.54854;-42.53097;,
 41.02884;22.60029;-41.02884;,
 65.27643;26.76975;0.00000;,
 46.15737;26.76975;-46.15737;,
 70.40505;25.54854;0.00000;,
 49.78386;25.54854;-49.78386;,
 72.52938;22.60029;0.00000;,
 51.28599;22.60029;-51.28599;,
 70.40505;19.65204;0.00000;,
 49.78386;19.65204;-49.78386;,
 65.27643;18.43080;0.00000;,
 46.15737;18.43080;-46.15737;,
 60.14784;19.65204;0.00000;,
 42.53097;19.65204;-42.53097;,
 0.00000;25.54854;-60.14784;,
 0.00000;22.60029;-58.02351;,
 0.00000;26.76975;-65.27643;,
 0.00000;25.54854;-70.40505;,
 0.00000;22.60029;-72.52938;,
 0.00000;19.65204;-70.40505;,
 0.00000;18.43080;-65.27643;,
 0.00000;19.65204;-60.14784;,
 -42.53097;25.54854;-42.53097;,
 -41.02884;22.60029;-41.02884;,
 -46.15737;26.76975;-46.15737;,
 -49.78386;25.54854;-49.78386;,
 -51.28599;22.60029;-51.28599;,
 -49.78386;19.65204;-49.78386;,
 -46.15737;18.43080;-46.15737;,
 -42.53097;19.65204;-42.53097;,
 -60.14784;25.54854;0.00000;,
 -58.02351;22.60029;0.00000;,
 -65.27643;26.76975;0.00000;,
 -70.40505;25.54854;0.00000;,
 -72.52938;22.60029;0.00000;,
 -70.40505;19.65204;0.00000;,
 -65.27643;18.43080;0.00000;,
 -60.14784;19.65204;0.00000;,
 -42.53097;25.54854;42.53097;,
 -41.02881;22.60029;41.02887;,
 -46.15737;26.76975;46.15737;,
 -49.78386;25.54854;49.78389;,
 -51.28596;22.60029;51.28599;,
 -49.78386;19.65204;49.78389;,
 -46.15737;18.43080;46.15737;,
 -42.53097;19.65204;42.53097;,
 0.00000;25.54854;60.14784;,
 0.00000;22.60029;58.02351;,
 0.00000;26.76975;65.27643;,
 0.00000;25.54854;70.40505;,
 0.00000;22.60029;72.52938;,
 0.00000;19.65204;70.40505;,
 0.00000;18.43080;65.27643;,
 0.00000;19.65204;60.14784;,
 42.53097;25.54854;42.53097;,
 41.02881;22.60029;41.02887;,
 46.15737;26.76975;46.15737;,
 49.78386;25.54854;49.78386;,
 51.28596;22.60029;51.28599;,
 49.78386;19.65204;49.78386;,
 46.15737;18.43080;46.15737;,
 42.53097;19.65204;42.53097;,
 0.00000;52.99176;-21.69339;,
 15.33954;52.99176;-15.33954;,
 12.62805;37.40952;-12.62805;,
 0.00000;37.40952;-17.85876;,
 21.69339;52.99176;0.00000;,
 17.85876;37.40952;0.00000;,
 15.33954;52.99176;15.33954;,
 12.62805;37.40952;12.62805;,
 0.00000;52.99176;21.69339;,
 0.00000;37.40952;17.85876;,
 -15.33954;52.99176;15.33954;,
 -12.62805;37.40952;12.62805;,
 -21.69339;52.99176;0.00000;,
 -17.85876;37.40952;0.00000;,
 -15.33954;52.99176;-15.33954;,
 -12.62805;37.40952;-12.62805;,
 10.92750;26.50854;-10.92750;,
 0.00000;26.50854;-15.45381;,
 15.45381;26.50854;0.00000;,
 10.92750;26.50854;10.92750;,
 0.00000;26.50854;15.45381;,
 -10.92750;26.50854;10.92747;,
 -15.45381;26.50854;0.00000;,
 -10.92750;26.50854;-10.92747;,
 11.37231;14.83287;-11.37231;,
 0.00000;14.83287;-16.08288;,
 16.08288;14.83287;0.00000;,
 11.37231;14.83287;11.37231;,
 0.00000;14.83287;16.08288;,
 -11.37231;14.83287;11.37231;,
 -16.08288;14.83287;0.00000;,
 -11.37231;14.83287;-11.37231;,
 13.81419;0.80013;-13.81419;,
 0.00000;0.80013;-19.53621;,
 19.53621;0.80013;0.00000;,
 13.81419;0.80013;13.81419;,
 0.00000;0.80013;19.53621;,
 -13.81419;0.80013;13.81419;,
 -19.53621;0.80013;0.00000;,
 -13.81419;0.80013;-13.81419;,
 0.00000;52.99176;0.00000;,
 0.00000;0.80013;0.00000;,
 0.00000;54.82317;-28.11663;,
 19.88145;54.82317;-19.88145;,
 16.04382;44.71041;-16.04382;,
 0.00000;44.71041;-22.68939;,
 28.11663;54.82317;0.00000;,
 22.68939;44.71041;0.00000;,
 19.88145;54.82317;19.88145;,
 16.04382;44.71041;16.04382;,
 0.00000;54.82317;28.11663;,
 0.00000;44.71041;22.68939;,
 -19.88145;54.82317;19.88145;,
 -16.04382;44.71041;16.04382;,
 -28.11663;54.82317;0.00000;,
 -22.68939;44.71041;0.00000;,
 -19.88145;54.82317;-19.88145;,
 -16.04382;44.71041;-16.04382;,
 0.00000;54.82317;0.00000;,
 19.88145;54.82317;-19.88145;,
 0.00000;54.82317;-28.11663;,
 28.11663;54.82317;0.00000;,
 19.88145;54.82317;19.88145;,
 0.00000;54.82317;28.11663;,
 -19.88145;54.82317;19.88145;,
 -28.11663;54.82317;0.00000;,
 -19.88145;54.82317;-19.88145;,
 0.00000;44.71041;0.00000;,
 0.00000;64.64154;-3.00999;,
 2.12838;64.64154;-2.12838;,
 3.73953;57.93924;-3.73953;,
 0.00000;57.93924;-5.28849;,
 3.00999;64.64154;0.00000;,
 5.28849;57.93924;0.00000;,
 2.12838;64.64154;2.12838;,
 3.73953;57.93924;3.73953;,
 0.00000;64.64154;3.00999;,
 0.00000;57.93924;5.28849;,
 -2.12838;64.64154;2.12838;,
 -3.73953;57.93924;3.73953;,
 -3.00999;64.64154;0.00000;,
 -5.28849;57.93924;0.00000;,
 -2.12838;64.64154;-2.12838;,
 -3.73953;57.93924;-3.73953;,
 0.00000;64.64154;0.00000;,
 0.00000;57.93924;0.00000;,
 0.00000;62.95143;-23.73102;,
 16.78038;62.95143;-16.78038;,
 10.76520;52.66464;-10.76520;,
 0.00000;52.66464;-15.22431;,
 23.73102;62.95143;0.00000;,
 15.22431;52.66464;0.00000;,
 16.78038;62.95143;16.78038;,
 10.76520;52.66464;10.76520;,
 0.00000;62.95143;23.73102;,
 0.00000;52.66464;15.22431;,
 -16.78038;62.95143;16.78038;,
 -10.76520;52.66464;10.76520;,
 -23.73102;62.95143;0.00000;,
 -15.22431;52.66464;0.00000;,
 -16.78038;62.95143;-16.78038;,
 -10.76520;52.66464;-10.76520;,
 0.00000;57.21642;0.00000;,
 0.00000;52.66464;0.00000;;
 
 232;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,19,20;,
 3;18,21,19;,
 3;18,22,21;,
 3;18,23,22;,
 3;18,24,23;,
 3;18,25,24;,
 3;18,26,25;,
 3;18,20,26;,
 3;27,3,2;,
 3;28,2,5;,
 3;29,5,7;,
 3;30,7,9;,
 3;31,9,11;,
 3;32,11,13;,
 3;33,13,15;,
 3;34,15,17;,
 4;35,36,37,38;,
 4;36,39,40,37;,
 4;39,41,42,40;,
 4;41,43,44,42;,
 4;43,45,46,44;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,35,38,50;,
 3;51,52,53;,
 3;51,53,54;,
 3;51,54,55;,
 3;51,55,56;,
 3;51,56,57;,
 3;51,57,58;,
 3;51,58,59;,
 3;51,59,52;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;71,70,72,73;,
 4;74,75,76,77;,
 4;77,76,78,79;,
 4;80,81,82,83;,
 4;83,82,61,60;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,84,87,99;,
 4;87,86,100,101;,
 4;86,89,102,100;,
 4;89,91,103,102;,
 4;91,93,104,103;,
 4;93,95,105,104;,
 4;95,97,106,105;,
 4;97,99,107,106;,
 4;99,87,101,107;,
 4;101,100,108,109;,
 4;100,102,110,108;,
 4;102,103,111,110;,
 4;103,104,112,111;,
 4;104,105,113,112;,
 4;105,106,114,113;,
 4;106,107,115,114;,
 4;107,101,109,115;,
 4;109,108,116,117;,
 4;108,110,118,116;,
 4;110,111,119,118;,
 4;111,112,120,119;,
 4;112,113,121,120;,
 4;113,114,122,121;,
 4;114,115,123,122;,
 4;115,109,117,123;,
 4;117,116,124,125;,
 4;116,118,126,124;,
 4;118,119,127,126;,
 4;119,120,128,127;,
 4;120,121,129,128;,
 4;121,122,130,129;,
 4;122,123,131,130;,
 4;123,117,125,131;,
 4;125,124,132,133;,
 4;124,126,134,132;,
 4;126,127,135,134;,
 4;127,128,136,135;,
 4;128,129,137,136;,
 4;129,130,138,137;,
 4;130,131,139,138;,
 4;131,125,133,139;,
 4;133,132,140,141;,
 4;132,134,142,140;,
 4;134,135,143,142;,
 4;135,136,144,143;,
 4;136,137,145,144;,
 4;137,138,146,145;,
 4;138,139,147,146;,
 4;139,133,141,147;,
 4;141,140,85,84;,
 4;140,142,88,85;,
 4;142,143,90,88;,
 4;143,144,92,90;,
 4;144,145,94,92;,
 4;145,146,96,94;,
 4;146,147,98,96;,
 4;147,141,84,98;,
 4;148,149,150,151;,
 4;149,152,153,150;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;156,158,159,157;,
 4;158,160,161,159;,
 4;160,162,163,161;,
 4;162,148,151,163;,
 4;151,150,164,165;,
 4;150,153,166,164;,
 4;153,155,167,166;,
 4;155,157,168,167;,
 4;157,159,169,168;,
 4;159,161,170,169;,
 4;161,163,171,170;,
 4;163,151,165,171;,
 4;165,164,172,173;,
 4;164,166,174,172;,
 4;166,167,175,174;,
 4;167,168,176,175;,
 4;168,169,177,176;,
 4;169,170,178,177;,
 4;170,171,179,178;,
 4;171,165,173,179;,
 4;173,172,180,181;,
 4;172,174,182,180;,
 4;174,175,183,182;,
 4;175,176,184,183;,
 4;176,177,185,184;,
 4;177,178,186,185;,
 4;178,179,187,186;,
 4;179,173,181,187;,
 3;188,149,148;,
 3;188,152,149;,
 3;188,154,152;,
 3;188,156,154;,
 3;188,158,156;,
 3;188,160,158;,
 3;188,162,160;,
 3;188,148,162;,
 3;189,181,180;,
 3;189,180,182;,
 3;189,182,183;,
 3;189,183,184;,
 3;189,184,185;,
 3;189,185,186;,
 3;189,186,187;,
 3;189,187,181;,
 4;190,191,192,193;,
 4;191,194,195,192;,
 4;194,196,197,195;,
 4;196,198,199,197;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;202,204,205,203;,
 4;204,190,193,205;,
 3;206,207,208;,
 3;206,209,207;,
 3;206,210,209;,
 3;206,211,210;,
 3;206,212,211;,
 3;206,213,212;,
 3;206,214,213;,
 3;206,208,214;,
 3;215,193,192;,
 3;215,192,195;,
 3;215,195,197;,
 3;215,197,199;,
 3;215,199,201;,
 3;215,201,203;,
 3;215,203,205;,
 3;215,205,193;,
 4;216,217,218,219;,
 4;217,220,221,218;,
 4;220,222,223,221;,
 4;222,224,225,223;,
 4;224,226,227,225;,
 4;226,228,229,227;,
 4;228,230,231,229;,
 4;230,216,219,231;,
 3;232,217,216;,
 3;232,220,217;,
 3;232,222,220;,
 3;232,224,222;,
 3;232,226,224;,
 3;232,228,226;,
 3;232,230,228;,
 3;232,216,230;,
 3;233,219,218;,
 3;233,218,221;,
 3;233,221,223;,
 3;233,223,225;,
 3;233,225,227;,
 3;233,227,229;,
 3;233,229,231;,
 3;233,231,219;,
 4;234,235,236,237;,
 4;235,238,239,236;,
 4;238,240,241,239;,
 4;240,242,243,241;,
 4;242,244,245,243;,
 4;244,246,247,245;,
 4;246,248,249,247;,
 4;248,234,237,249;,
 3;250,235,234;,
 3;250,238,235;,
 3;250,240,238;,
 3;250,242,240;,
 3;250,244,242;,
 3;250,246,244;,
 3;250,248,246;,
 3;250,234,248;,
 3;251,237,236;,
 3;251,236,239;,
 3;251,239,241;,
 3;251,241,243;,
 3;251,243,245;,
 3;251,245,247;,
 3;251,247,249;,
 3;251,249,237;;
 
 MeshMaterialList {
  5;
  232;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  4,
  3,
  3,
  4,
  4,
  3,
  3,
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
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/Game/fountain_koke.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/Game/fountain_koke.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/Game/fountain_koke_s.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/Game/fountain_koke_s.png";
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
  191;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  0.707107;0.000000;0.707107;,
  -0.811326;0.584594;0.000000;,
  -0.548852;0.835920;0.000000;,
  -0.000002;1.000000;0.000000;,
  0.548851;0.835920;0.000000;,
  0.811328;0.584592;0.000000;,
  0.548853;-0.835919;0.000000;,
  -0.000002;-1.000000;0.000000;,
  -0.548854;-0.835918;0.000000;,
  -0.573695;0.584593;0.573695;,
  -0.388097;0.835920;0.388097;,
  -0.000001;1.000000;0.000001;,
  0.388096;0.835921;-0.388096;,
  0.573695;0.584593;-0.573695;,
  0.388098;-0.835919;-0.388098;,
  -0.000001;-1.000000;0.000001;,
  -0.388098;-0.835918;0.388098;,
  0.000000;0.584593;0.811327;,
  0.000000;0.835920;0.548852;,
  0.000000;1.000000;0.000002;,
  0.000000;0.835921;-0.548850;,
  0.000000;0.584593;-0.811327;,
  0.000000;-0.835919;-0.548853;,
  0.000000;-1.000000;0.000002;,
  0.000000;-0.835918;0.548854;,
  0.573695;0.584593;0.573695;,
  0.388097;0.835920;0.388097;,
  0.000001;1.000000;0.000001;,
  -0.388096;0.835921;-0.388096;,
  -0.573695;0.584593;-0.573695;,
  -0.388098;-0.835919;-0.388098;,
  0.000001;-1.000000;0.000001;,
  0.388098;-0.835918;0.388098;,
  0.811326;0.584594;0.000000;,
  0.548852;0.835920;0.000000;,
  0.000002;1.000000;-0.000000;,
  -0.548851;0.835920;0.000000;,
  -0.811328;0.584591;0.000001;,
  -0.548853;-0.835919;0.000000;,
  0.000002;-1.000000;-0.000000;,
  0.548854;-0.835918;0.000000;,
  0.573694;0.584593;-0.573695;,
  0.388097;0.835920;-0.388097;,
  0.000001;1.000000;-0.000001;,
  -0.388097;0.835919;0.388097;,
  -0.573697;0.584589;0.573697;,
  -0.388099;-0.835918;0.388099;,
  0.000001;-1.000000;-0.000001;,
  0.388098;-0.835918;-0.388099;,
  0.000000;0.584592;-0.811328;,
  0.000000;0.835919;-0.548853;,
  0.000000;1.000000;-0.000002;,
  -0.000000;0.835920;0.548851;,
  -0.000000;0.584590;0.811328;,
  -0.000000;-0.835918;0.548854;,
  0.000000;-1.000000;-0.000002;,
  0.000000;-0.835918;-0.548855;,
  -0.573694;0.584593;-0.573695;,
  -0.388097;0.835920;-0.388097;,
  -0.000001;1.000000;-0.000001;,
  0.388097;0.835920;0.388097;,
  0.573696;0.584591;0.573696;,
  0.388098;-0.835918;0.388098;,
  -0.000001;-1.000000;-0.000001;,
  -0.388098;-0.835918;-0.388099;,
  0.811328;-0.584592;0.000000;,
  0.573695;-0.584593;-0.573695;,
  -0.811326;-0.584594;0.000000;,
  -0.573695;-0.584593;0.573695;,
  0.000000;-0.584593;-0.811327;,
  0.000000;-0.584593;0.811327;,
  -0.573695;-0.584593;-0.573695;,
  0.573695;-0.584593;0.573695;,
  -0.811328;-0.584591;0.000001;,
  0.811326;-0.584594;0.000000;,
  -0.573697;-0.584589;0.573697;,
  0.573694;-0.584593;-0.573695;,
  -0.000000;-0.584590;0.811328;,
  0.000000;-0.584592;-0.811328;,
  0.573696;-0.584591;0.573696;,
  -0.573694;-0.584593;-0.573695;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.238960;-0.971029;,
  0.686621;-0.238960;-0.686621;,
  0.971029;-0.238960;-0.000000;,
  0.686621;-0.238960;0.686621;,
  0.000000;-0.238960;0.971029;,
  -0.686621;-0.238960;0.686621;,
  -0.971029;-0.238960;0.000000;,
  -0.686621;-0.238960;-0.686621;,
  -0.000000;-0.227220;-0.973843;,
  0.688611;-0.227220;-0.688611;,
  0.973844;-0.227220;-0.000000;,
  0.688611;-0.227220;0.688611;,
  -0.000000;-0.227220;0.973843;,
  -0.688611;-0.227220;0.688611;,
  -0.973843;-0.227220;0.000000;,
  -0.688611;-0.227220;-0.688611;,
  -0.000001;-0.081783;-0.996650;,
  0.704738;-0.081783;-0.704738;,
  0.996650;-0.081783;-0.000000;,
  0.704738;-0.081783;0.704738;,
  -0.000001;-0.081783;0.996650;,
  -0.704738;-0.081783;0.704738;,
  -0.996650;-0.081783;0.000000;,
  -0.704738;-0.081783;-0.704738;,
  -0.000000;0.147212;-0.989105;,
  0.699403;0.147212;-0.699403;,
  0.989105;0.147212;0.000000;,
  0.699403;0.147212;0.699403;,
  -0.000000;0.147212;0.989105;,
  -0.699403;0.147212;0.699403;,
  -0.989105;0.147212;0.000000;,
  -0.699403;0.147212;-0.699403;,
  0.000000;0.238962;-0.971029;,
  0.686621;0.238962;-0.686621;,
  0.971029;0.238962;0.000000;,
  0.686621;0.238962;0.686621;,
  0.000000;0.238962;0.971029;,
  -0.686621;0.238962;0.686621;,
  -0.971029;0.238962;0.000000;,
  -0.686621;0.238962;-0.686621;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.472877;-0.881128;,
  0.623052;-0.472877;-0.623052;,
  0.881128;-0.472877;-0.000000;,
  0.623052;-0.472877;0.623052;,
  0.000000;-0.472877;0.881128;,
  -0.623052;-0.472877;0.623052;,
  -0.881128;-0.472877;0.000000;,
  -0.623052;-0.472877;-0.623052;,
  0.000000;1.000000;0.000000;,
  0.000000;0.321867;-0.946785;,
  0.669478;0.321867;-0.669478;,
  0.946785;0.321867;0.000000;,
  0.669478;0.321867;0.669478;,
  0.000000;0.321867;0.946785;,
  -0.669478;0.321867;0.669478;,
  -0.946785;0.321867;0.000000;,
  -0.669478;0.321867;-0.669478;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.637280;-0.770632;,
  0.544919;-0.637280;-0.544919;,
  0.770632;-0.637280;-0.000000;,
  0.544919;-0.637280;0.544919;,
  0.000000;-0.637280;0.770632;,
  -0.544919;-0.637280;0.544919;,
  -0.770632;-0.637280;0.000000;,
  -0.544919;-0.637280;-0.544919;,
  0.000000;-0.909589;-0.415508;,
  0.293809;-0.909589;-0.293809;,
  0.415508;-0.909589;-0.000000;,
  0.293809;-0.909589;0.293809;,
  0.000000;-0.909589;0.415508;,
  -0.293809;-0.909589;0.293809;,
  -0.415508;-0.909589;0.000000;,
  -0.293809;-0.909589;-0.293809;,
  0.000000;-1.000000;-0.000000;,
  -0.166103;0.972018;0.166103;,
  0.000000;0.972018;0.234905;,
  -0.234905;0.972018;0.000000;,
  -0.166103;0.972018;-0.166103;,
  0.000000;0.972018;-0.234905;,
  0.166103;0.972018;-0.166103;,
  0.234905;0.972018;0.000000;,
  0.166103;0.972018;0.166103;;
  232;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,10,10,17;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  4;19,19,20,20;,
  4;20,20,16,16;,
  4;16,16,21,21;,
  4;21,21,22,22;,
  4;22,22,23,23;,
  4;23,23,12,12;,
  4;12,12,24,24;,
  4;24,24,19,19;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;89,30,38,90;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,91,92,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;90,38,46,93;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,92,94,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;93,46,54,95;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,94,96,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;95,54,62,97;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,96,98,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;97,62,70,99;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,98,100,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;99,70,78,101;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,100,102,80;,
  4;73,74,82,81;,
  4;74,75,83,82;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;101,78,86,103;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,102,104,88;,
  4;81,82,26,25;,
  4;82,83,27,26;,
  4;83,84,28,27;,
  4;84,85,29,28;,
  4;103,86,30,89;,
  4;86,87,31,30;,
  4;87,88,32,31;,
  4;88,104,91,32;,
  4;106,107,115,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;109,110,118,117;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;113,106,114,121;,
  4;114,115,123,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;117,118,126,125;,
  4;118,119,127,126;,
  4;119,120,128,127;,
  4;120,121,129,128;,
  4;121,114,122,129;,
  4;122,123,131,130;,
  4;123,124,132,131;,
  4;124,125,133,132;,
  4;125,126,134,133;,
  4;126,127,135,134;,
  4;127,128,136,135;,
  4;128,129,137,136;,
  4;129,122,130,137;,
  4;130,131,139,138;,
  4;131,132,140,139;,
  4;132,133,141,140;,
  4;133,134,142,141;,
  4;134,135,143,142;,
  4;135,136,144,143;,
  4;136,137,145,144;,
  4;137,130,138,145;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  4;147,148,148,147;,
  4;148,149,149,148;,
  4;149,150,150,149;,
  4;150,151,151,150;,
  4;151,152,152,151;,
  4;152,153,153,152;,
  4;153,154,154,153;,
  4;154,147,147,154;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;105,105,105;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  3;146,146,146;,
  4;156,157,157,156;,
  4;157,158,158,157;,
  4;158,159,159,158;,
  4;159,160,160,159;,
  4;160,161,161,160;,
  4;161,162,162,161;,
  4;162,163,163,162;,
  4;163,156,156,163;,
  3;155,155,155;,
  3;155,155,155;,
  3;155,155,155;,
  3;155,155,155;,
  3;155,155,155;,
  3;155,155,155;,
  3;155,155,155;,
  3;155,155,155;,
  3;164,164,164;,
  3;164,164,164;,
  3;164,164,164;,
  3;164,164,164;,
  3;164,164,164;,
  3;164,164,164;,
  3;164,164,164;,
  3;164,164,164;,
  4;166,167,175,174;,
  4;167,168,176,175;,
  4;168,169,177,176;,
  4;169,170,178,177;,
  4;170,171,179,178;,
  4;171,172,180,179;,
  4;172,173,181,180;,
  4;173,166,174,181;,
  3;165,183,184;,
  3;165,185,183;,
  3;165,186,185;,
  3;165,187,186;,
  3;165,188,187;,
  3;165,189,188;,
  3;165,190,189;,
  3;165,184,190;,
  3;182,174,175;,
  3;182,175,176;,
  3;182,176,177;,
  3;182,177,178;,
  3;182,178,179;,
  3;182,179,180;,
  3;182,180,181;,
  3;182,181,174;;
 }
 MeshTextureCoords {
  252;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.525950;0.369338;,
  0.760142;0.095589;,
  0.957893;0.296006;,
  0.425205;0.055531;,
  0.149283;0.199297;,
  0.094008;0.442670;,
  0.291759;0.643087;,
  0.626696;0.683145;,
  0.902618;0.539379;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.500000;0.136364;,
  1.254564;0.136364;,
  1.254564;0.429554;,
  0.500000;0.429554;,
  1.567114;0.136364;,
  1.567114;0.429554;,
  1.254564;0.136364;,
  1.254564;0.429554;,
  0.500000;0.136364;,
  0.500000;0.429554;,
  -0.254564;0.136364;,
  -0.254564;0.429554;,
  -0.567114;0.136364;,
  -0.567114;0.429554;,
  -0.254564;0.136364;,
  -0.254564;0.429554;,
  0.525944;0.369331;,
  0.886895;0.308051;,
  0.721646;0.140575;,
  0.441757;0.107100;,
  0.211185;0.227237;,
  0.164994;0.430610;,
  0.330243;0.598087;,
  0.610132;0.631562;,
  0.840704;0.511425;,
  0.500000;0.136690;,
  0.500000;0.429879;,
  1.254564;0.429879;,
  1.254564;0.136690;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  1.567114;0.136690;,
  1.567114;0.429879;,
  1.254564;0.429879;,
  1.254564;0.136690;,
  0.500000;0.429879;,
  0.500000;0.136690;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  -0.567114;0.136690;,
  -0.567114;0.429879;,
  -0.254564;0.429879;,
  -0.254564;0.136690;,
  0.447929;0.129660;,
  0.444860;0.120634;,
  0.707791;0.152081;,
  0.701575;0.159996;,
  0.438002;0.099495;,
  0.723352;0.133623;,
  0.431373;0.078625;,
  0.739143;0.115434;,
  0.428856;0.070250;,
  0.745912;0.108169;,
  0.431925;0.079275;,
  0.739695;0.116085;,
  0.438783;0.100415;,
  0.724134;0.134543;,
  0.445412;0.121285;,
  0.708344;0.152731;,
  0.863029;0.309411;,
  0.851329;0.311770;,
  0.891827;0.304368;,
  0.920854;0.299594;,
  0.933106;0.297886;,
  0.921406;0.300245;,
  0.892608;0.305288;,
  0.863582;0.310062;,
  0.819637;0.500464;,
  0.809470;0.496074;,
  0.844735;0.511710;,
  0.870062;0.523227;,
  0.880781;0.528267;,
  0.870614;0.523878;,
  0.845516;0.512631;,
  0.820190;0.501114;,
  0.603033;0.613322;,
  0.600516;0.604947;,
  0.609662;0.634192;,
  0.616520;0.655332;,
  0.619590;0.664357;,
  0.617073;0.655982;,
  0.610444;0.635112;,
  0.603586;0.613972;,
  0.340102;0.581876;,
  0.346871;0.574611;,
  0.324312;0.600064;,
  0.308750;0.618522;,
  0.302534;0.626437;,
  0.309303;0.619173;,
  0.325093;0.600984;,
  0.340654;0.582526;,
  0.184864;0.424545;,
  0.197116;0.422837;,
  0.155837;0.429319;,
  0.127039;0.434362;,
  0.115340;0.436721;,
  0.127592;0.435013;,
  0.156619;0.430239;,
  0.185417;0.425196;,
  0.228256;0.233493;,
  0.238976;0.238533;,
  0.202930;0.221976;,
  0.177831;0.210729;,
  0.167664;0.206340;,
  0.178384;0.211380;,
  0.203711;0.222897;,
  0.228809;0.234143;,
  0.500000;-0.109211;,
  0.755659;-0.109211;,
  0.710467;0.150493;,
  0.500000;0.150493;,
  0.861557;-0.109211;,
  0.797646;0.150493;,
  0.755659;-0.109211;,
  0.710467;0.150493;,
  0.500000;-0.109211;,
  0.500000;0.150493;,
  0.244341;-0.109211;,
  0.289533;0.150493;,
  0.138443;-0.109211;,
  0.202354;0.150493;,
  0.244341;-0.109211;,
  0.289533;0.150493;,
  0.682125;0.332176;,
  0.500000;0.332176;,
  0.757563;0.332176;,
  0.682125;0.332176;,
  0.500000;0.332176;,
  0.317875;0.332176;,
  0.242436;0.332176;,
  0.317875;0.332176;,
  0.689538;0.526770;,
  0.500000;0.526770;,
  0.768048;0.526770;,
  0.689538;0.526770;,
  0.500000;0.526770;,
  0.310462;0.526770;,
  0.231952;0.526770;,
  0.310462;0.526770;,
  0.730236;0.760650;,
  0.500000;0.760650;,
  0.825603;0.760650;,
  0.730236;0.760650;,
  0.500000;0.760650;,
  0.269764;0.760650;,
  0.174397;0.760650;,
  0.269764;0.760650;,
  0.500000;-0.109211;,
  0.500000;0.760650;,
  0.500000;-0.139734;,
  0.831357;-0.139734;,
  0.767397;0.028812;,
  0.500000;0.028812;,
  0.968611;-0.139734;,
  0.878157;0.028812;,
  0.831357;-0.139734;,
  0.767397;0.028812;,
  0.500000;-0.139734;,
  0.500000;0.028812;,
  0.168643;-0.139734;,
  0.232603;0.028812;,
  0.031390;-0.139734;,
  0.121843;0.028812;,
  0.168643;-0.139734;,
  0.232603;0.028812;,
  0.500000;0.412424;,
  0.831357;0.742256;,
  0.500000;0.878877;,
  0.968611;0.412424;,
  0.831357;0.082592;,
  0.500000;-0.054029;,
  0.168643;0.082592;,
  0.031390;0.412424;,
  0.168643;0.742256;,
  0.500000;0.028812;,
  0.500000;0.446675;,
  0.535473;0.432049;,
  0.562325;0.469485;,
  0.500000;0.495182;,
  0.550166;0.396740;,
  0.588142;0.407446;,
  0.535473;0.361430;,
  0.562325;0.345408;,
  0.500000;0.346804;,
  0.500000;0.319710;,
  0.464527;0.361430;,
  0.437674;0.345408;,
  0.449834;0.396740;,
  0.411858;0.407446;,
  0.464527;0.432049;,
  0.437674;0.469485;,
  0.500000;0.396740;,
  0.500000;0.407446;,
  0.500000;0.793136;,
  0.779673;0.677825;,
  0.679420;0.594466;,
  0.500000;0.668442;,
  0.895517;0.399440;,
  0.753739;0.415872;,
  0.779673;0.121054;,
  0.679420;0.237278;,
  0.500000;0.005743;,
  0.500000;0.163302;,
  0.220327;0.121054;,
  0.320580;0.237278;,
  0.104483;0.399440;,
  0.246262;0.415872;,
  0.220327;0.677825;,
  0.320580;0.594466;,
  0.500000;0.408601;,
  0.500000;0.415872;;
 }
}
