
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterVrml97.h"
#include "SynEditStrConst.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace Synhighlighterhashentries;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;
using namespace System::Uitypes;
using namespace Vcl::Graphics;

namespace Synhighlightervrml97
{
#define SynHighlighterVrml97__0 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__1 TFontStyles()
#define SynHighlighterVrml97__2 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__3 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__4 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__5 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__6 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__7 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__8 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__9 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__10 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__11 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__12 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__13 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__14 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__15 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__16 (TFontStyles() << TFontStyle::fsItalic << TFontStyle::fsBold)
#define SynHighlighterVrml97__17 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__18 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__19 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__20 (TFontStyles() << TFontStyle::fsBold)
#define SynHighlighterVrml97__21 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__22 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__23 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__24 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__25 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__26 (TFontStyles() << TFontStyle::fsItalic)
#define SynHighlighterVrml97__27 (TSysCharSet() << L'=' << L'&')
#define SynHighlighterVrml97__28 (TSysCharSet() << L'=' << L'-' << L'>')
#define SynHighlighterVrml97__29 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57 <<  \
										97 << 98 << 99 << 100 << 101 << 102 <<  \
										65 << 66 << 67 << 68 << 69 << 70)
#define SynHighlighterVrml97__30 (TSysCharSet() << L'=' << L'|')
#define SynHighlighterVrml97__31 (TSysCharSet() << L'=' << L'+')


const String Events = L"onAbort, onBlur, onChange, onClick, onDblClick, onError, onFocus, "
	           L"onKeyDown, onKeyPress, onKeyUp, onLoad, onMouseDown, onMouseMove, "
	           L"onMouseOut, onMouseOver, onMouseUp, onReset, onSelect, onSubmit, "
	           L"onUnload";
const String Keywords = L"abstract, boolean, break, byte, callee, case, catch, char, class, "
	           L"const, constructor, continue, debugger, default, delete, do, DOCTYPE, "
	           L"double, else, enum, export, extends, false, final, finally, float, for, "
	           L"function, goto, head, if, implements, import, in, instanceof, int, "
	           L"interface, long, meta, NaN, native, new, null, package, private, "
	           L"protected, prototype, public, PUBLIC, return, short, start, static, "
	           L"super, switch, synchronized, this, throw, throws, transient, true, try, "
	           L"typeof, var, void, while, with, xml";
const String NonReservedKeys = L"abs, acos, action, alert, align, alinkColor, all, All, anchor, anchors, "
	           L"appCodeName, Applet, applets, appName, appVersion, Area, arguments, "
	           L"Arguments, Array, asin, atan, atan2, back, background, bgColor, big, "
	           L"blink, blur, body, bold, Boolean, border, Button, call, caller, "
	           L"captureEvents, ceil, charAt, charCodeAt, Checkbox, checked, clear, "
	           L"clearInterval, clearTimeout, click, close, closed, complete, concat, "
	           L"confirm, content, cookie, cos, current, Date, defaultChecked, "
	           L"defaultSelected, defaultStatus, defaultValue, display, document, "
	           L"domain, E, elements, Embed, embeds, enabledPlugin, encoding, escape, "
	           L"eval, event, exp, fgColor, filename, FileUpload, find, fixed, Float, "
	           L"floor, focus, fontcolor, fontsize, form, Form, forms, forward, Frame, "
	           L"frames, fromCharCode, Function, getDate, getDay, getElementById, "
	           L"getFullYear, getHours, getMilliseconds, getMinutes, getMonth, "
	           L"getSeconds, getTime, getTimezoneOffset, getUTCDate, getUTCDay, "
	           L"getUTCFullYear, getUTCHours, getUTCMilliseconds, getUTCMinutes, "
	           L"getUTCMonth, getUTCSeconds, getYear, Global, go, handleEvent, hash, "
	           L"Hidden, history, History, home, host, hostname, href, hspace, Image, "
	           L"images, index, indexOf, Infinity, innerHeight, innerWidth, input, "
	           L"isFinite, isNaN, italics, java, javaEnabled, join, lastIndexOf, "
	           L"lastModified, Layer, layers, left, link, Link, linkColor, links, LN10, "
	           L"LN2, Location, locationbar, log, LOG10E, LOG2E, logon, lowsrc, match, "
	           L"Math, max, MAX_VALUE, menubar, method, MimeType, mimeTypes, min, "
	           L"MIN_VALUE, moveBy, moveTo, name, navigator, Navigator, "
	           L"NEGATIVE_INFINITY, netscape, next, Null, Number, Object, open, opener, "
	           L"Option, options, outerHeight, outerWidth, Packages, pageX, pageXOffset, "
	           L"pageY, pageYOffset, parent, parse, parseFloat, parseInt, Password, "
	           L"pathname, personalbar, PI, platform, Plugin, plugins, port, "
	           L"POSITIVE_INFINITY, pow, previous, print, prompt, protocol, Radio, "
	           L"random, referrer, refresh, RegExp, releaseEvents, reload, replace, "
	           L"reset, Reset, resizeBy, resizeTo, reverse, right, round, routeEvent, "
	           L"screen, scroll, scrollbars, scrollBy, scrollTo, search, select, Select, "
	           L"selected, selectedIndex, self, setDate, setFullYear, setHours, "
	           L"setInterval, setMilliseconds, setMinutes, setMonth, setSeconds, "
	           L"setTime, setTimeout, setUTCDate, setUTCFullYear, setUTCHours, "
	           L"setUTCMilliseconds, setUTCMinutes, setUTCMonth, setUTCSeconds, setYear, "
	           L"sin, slice, small, sort, split, sqrt, SQRT1_2, SQRT2, src, status, "
	           L"statusbar, stop, strike, String, sub, submit, Submit, substr, "
	           L"substring, suffixes, sup, tags, taint, taintEnabled, tan, target, text, "
	           L"Textarea, title, toGMTString, toLocaleString, toLowerCase, toolbar, "
	           L"toSource, toString, toUpperCase, toUTCString, undefined, Undefined, "
	           L"unescape, untaint, unwatch, URL, userAgent, UTC, value, valueOf, "
	           L"version, visibility, vlinkColor, vspace, watch, width, window, Window, "
	           L"write, writeln, zIndex";
const String VrmlAppearances = L"Appearance, ImageTexture, Material, NurbsTextureSurface, PixelTexture, "
	           L"TextureBackground, TextureCoordinate, TextureCoordinateGenerator, "
	           L"TextureTransform";
const String VrmlAttributes = L"addChildren, ambientIntensity, appearance, attenuation, autoOffset, "
	           L"avatarSize, axisOfRotation, backUrl, bboxCenter, bboxSize, beamWidth, "
	           L"beginCap, bindTime, bottom, bottomRadius, bottomUrl, ccw, center, children, "
	           L"choice, collide, collideTime, color, colorIndex, colorPerVertex, "
	           L"ColorRGBA, convex, coord, coordIndex, creaseAngle, crossSection, "
	           L"cutOffAngle, cycleInterval, cycleTime, description, diffuseColor, direction, "
	           L"directOutput, diskAngle, duration_changed, emissiveColor, enabled, "
	           L"endCap, enterTime, eventName, eventType, exitTime, family, fieldName, "
	           L"fieldOfView, fieldType, FillProperties, fogType, fontStyle, "
	           L"fraction_changed, frontUrl, GeoCoordinate, GeoElevationGrid, "
	           L"GeoLocation, GeoLOD, GeoMetadata, geometry, GeoOrigin, groundAngle, "
	           L"groundColor, headlight, height, hitNormal_changed, hitPoint_changed, "
	           L"hitTexCoord_changed, horizontal, image, info, intensity, isActive, "
	           L"isBound, isOver, jump, justify, key, keyValue, language, leftToRight, "
	           L"leftUrl, length, level, LineProperties, location, loop, material, maxAngle, "
	           L"maxBack, maxExtent, maxFront, maxPosition, minAngle, minBack, minFront, "
	           L"minPosition, MultiTexture, MultiTextureCoordinate, mustEvaluate, "
	           L"normal, normalIndex, normalPerVertex, offset, on, orientation, "
	           L"orientation_changed, parameter, pitch, point, position, "
	           L"position_changed, priority, proxy, radius, range, removeChildren, "
	           L"repeatS, repeatT, rightUrl, rotation, rotation_changed, scale, "
	           L"scaleOrientation, set_bind, set_colorIndex, set_coordIndex, "
	           L"set_crossSection, set_fraction, set_height, set_normalIndex, "
	           L"set_orientation, set_scale, set_spine, set_texCoordIndex, shininess, "
	           L"side, size, skyAngle, skyColor, solid, source, spacing, spatialize, "
	           L"specularColor, speed, spine, startTime, stopTime, string, style, texCoord, "
	           L"texCoordIndex, texture, textureTransform, time, top, topToBottom, "
	           L"topUrl, touchTime, trackPoint_changed, translation, "
	           L"translation_changed, transparency, type, url, value_changed, vector, "
	           L"visibilityLimit, visibilityRange, whichChoice, xDimension, xSpacing, "
	           L"zDimension, zSpacing";
const String VrmlDefinitions = L"MFColor, MFFloat, MFInt32, MFNode, MFRotation, MFString, MFTime, "
	           L"MFVec2f, MFVec3f, SFBool, SFColor, SFFloat, SFImage, SFInt32, SFNode, "
	           L"SFRotation, SFString, SFTime, SFVec2f, SFVec3f";
const String VrmlEvents = L"eventIn, eventOut, exposedField, field";
const String VrmlGroupings = L"Anchor, Billboard, Collision, ESPDUTransform, Group, Inline, LOD, "
	           L"NurbsGroup, ReceiverPdu, SignalPdu, StaticGroup, Switch, Transform, "
	           L"Transform2D, TransmitterPdu";
const String VrmlInterpolators = L"ColorInterpolator, CoordinateInterpolator, CoordinateInterpolator2D, "
	           L"GeoPositionInterpolator, NormalInterpolator, NurbsPositionInterpolator, "
	           L"OrientationInterpolator, PositionInterpolator, PositionInterpolator2D, "
	           L"ScalarInterpolator";
const String VrmlLights = L"DirectionalLight, PointLight, SpotLight";
const String VrmlNodes = L"Background, Color, Coordinate, CoordinateDeformer, Fog, FontStyle, "
	           L"Joint, NavigationInfo, Normal, Script, Site, Sound";
const String VrmlParameters = L"ALL, AUTO, BINDINGS, BOLD, BOTTOM, CENTER, CLAMP, CLOCKWISE, CONVEX, "
	           L"COUNTERCLOCKWISE, CULLING, DEFAULT, DEFAULTS, Displacer, ENUMS, FACE, FALSE, "
	           L"FAMILY, FILE, FORMAT, ITALIC, JUSTIFICATION, LEFT, NONE, NULL, OFF, ON, "
	           L"OVERALL, PARTS, PER_FACE, PER_FACE_INDEXED, PER_PART, PER_PART_INDEXED, "
	           L"PER_VERTEX, PER_VERTEX_INDEXED, REPEAT, RIGHT, SHAPE, SIDES, SOLID, "
	           L"STYLE, TRUE, TYPE, UNKNOWN_FACE_TYPE, UNKNOWN_ORDERING, "
	           L"UNKNOWN_SHAPE_TYPE, WRAP";
const String VrmlProtos = L"DEF, EXTERNPROTO, IS, PROTO, ROUTE, Scene, TO, USE, VRML, X3D, "
	           L"X3DAppearanceNode, X3DAppearanceChildNode, X3DBackgroundNode, X3DBindableNode, "
	           L"X3DBoundedObject, X3DChildNode, X3DColorNode, X3DComposedGeometryNode, "
	           L"X3DCoordinateNode, X3DDragSensorNode, X3DEnvironmentalSensorNode, "
	           L"X3DFontStyleNode, X3DGeometry2DNode, X3DGeometry3DNode, "
	           L"X3DGeometryNode, X3DGeometryPropertyNode, X3DGroupingNode, "
	           L"X3DInterpolatorNode, X3DKeyDeviceSensorNode, X3DLightNode, "
	           L"X3DMaterialNode, X3DNetworkSensorNode, X3DNode, X3DNormalNode, "
	           L"X3DParametricGeometryNode, X3DPointingDeviceSensorNode, "
	           L"X3DPrototypeInstance, X3DScriptNode, X3DSensorNode, X3DSequencerNode, "
	           L"X3DShapeNode, X3DSoundNode, X3DSoundSourceNode, X3DTexture2DNode, "
	           L"X3DTextureCoordinateNode, X3DTextureNode, X3DTextureTransform2DNode, "
	           L"X3DTextureTransformNode, X3DTimeDependentNode, X3DTouchSensorNode, "
	           L"X3DTriggerNode, X3DUrlObject";
const String VrmlSensors = L"BooleanFilter, BooleanSequencer, BooleanToggle, BooleanTrigger, "
	           L"CylinderSensor, GeoTouchSensor, IntegerTrigger, KeySensor, LoadSensor, "
	           L"PlaneSensor, ProximitySensor, SphereSensor, StringSensor, TimeSensor, "
	           L"TouchSensor, VisibilitySensor";
const String VrmlShapes = L"Arc2D, ArcClose2D, Box, Circle2D, Cone, Contour2D, ContourPolyline2D, "
	           L"Cylinder, Disk2D, ElevationGrid, Humanoid, NurbsCurve, NurbsCurve2D, "
	           L"NurbsSurface, PointSet, Polyline2D, Polypoint2D, Rectangle2D, Segment, "
	           L"Shape, Shape2D, Sphere, Text, TriangleFanSet, TriangleSet, TriangleSet2D, "
	           L"TriangleStripSet, TrimmedSurface";
const String VrmlShape_Hints = L"Extrusion, IndexedFaceSet, IndexedLineSet";
const String VrmlTime_dependents = L"AudioClip, IntegerSequencer, MovieTexture, TimeTrigger";
const String VrmlViewpoints = L"GeoViewpoint, Viewpoint";
const String VrmlWorldInfos = L"WorldInfo";

void __fastcall TSynVrml97Syn::DoAddKeyword(String AKeyword, int AKind)
{
	int HashValue = 0;
	HashValue = HashKey(ustr2pwchar(AKeyword));
	fKeywords->Items[HashValue] = new TSynHashEntry(AKeyword, AKind);
}

int __fastcall TSynVrml97Syn::HashKey(PWideChar Str)
{
	int result = 0;

	auto GetOrd = [&]() -> int 
	{
		int result = 0;
		switch((*Str))
		{
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = 1 + int((*Str)) - int(L'a');
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			result = 27 + int((*Str)) - int(L'A');
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			result = 54 + int((*Str)) - int(L'0');
			break;
			case L'_':
			result = 53;
			break;
			default:
			result = 0;
			break;
		}
		return result;
	};
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (7 * result + GetOrd()) & 0xFFFFFF;
		++Str;
	}
	result = result & 0xFF; // 255
	fStringLen = Str - fToIdent;
	return result;
}

TtkTokenKind __fastcall TSynVrml97Syn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkComment;
	TSynHashEntry* Entry = nullptr;
	fToIdent = Maybe;
	Entry = fKeywords->Items[HashKey(Maybe)];
	while(ASSIGNED(Entry))
	{
		if(Entry->KeywordLen > fStringLen)
			break;
		else
		{
			if(Entry->KeywordLen == fStringLen)
			{
				if(IsCurrentToken(Entry->Keyword))
				{
					result = ((TtkTokenKind) Entry->Kind);
					return result;
				}
			}
		}
		Entry = Entry->Next;
	}
	result = tkIdentifier;
	return result;
}

__fastcall TSynVrml97Syn::TSynVrml97Syn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsNormalText),
			isDoctype(false),
			FTokenID(tkComment),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fKeyAttri(nullptr),
			fNonReservedKeyAttri(nullptr),
			fEventAttri(nullptr),
			fNumberAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fVrmlAppearanceAttri(nullptr),
			fVrmlAttributeAttri(nullptr),
			fVrmlDefinitionAttri(nullptr),
			fVrmlEventAttri(nullptr),
			fVrmlGroupingAttri(nullptr),
			fVrmlInterpolatorAttri(nullptr),
			fVrmlLightAttri(nullptr),
			fVrmlNodeAttri(nullptr),
			fVrmlParameterAttri(nullptr),
			fVrmlprotoAttri(nullptr),
			fVrmlSensorAttri(nullptr),
			fVrmlShapeAttri(nullptr),
			fVrmlShape_HintAttri(nullptr),
			fVrmlTime_dependentAttri(nullptr),
			fVrmlViewpointAttri(nullptr),
			fVrmlWorldInfoAttri(nullptr),
			fX3DDocTypeAttri(nullptr),
			fX3DHeaderAttri(nullptr),
			fKeywords(nullptr)
{
	FCaseSensitive = true;
	fKeywords = new TSynHashEntryList();
	isDoctype = false;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = SynHighlighterVrml97__0;
	fCommentAttri->Foreground = clNavy;
	fCommentAttri->Background = clGray;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fIdentifierAttri->Style = SynHighlighterVrml97__1;
	fIdentifierAttri->Foreground = clNavy;
	fIdentifierAttri->Background = clWhite;
	addAttribute(fIdentifierAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = SynHighlighterVrml97__2;
	fKeyAttri->Foreground = clRed;
	fKeyAttri->Background = clWhite;
	addAttribute(fKeyAttri);
	fNonReservedKeyAttri = new TSynHighlighterAttributes(SYNS_AttrNonReservedKeyword, SYNS_FriendlyAttrNonReservedKeyword);
	fNonReservedKeyAttri->Style = SynHighlighterVrml97__3;
	fNonReservedKeyAttri->Foreground = clBlack;
	fNonReservedKeyAttri->Background = clWhite;
	addAttribute(fNonReservedKeyAttri);
	fEventAttri = new TSynHighlighterAttributes(SYNS_AttrEvent, SYNS_FriendlyAttrEvent);
	fEventAttri->Style = SynHighlighterVrml97__4;
	fEventAttri->Foreground = clNavy;
	fEventAttri->Background = clWhite;
	addAttribute(fEventAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fEventAttri->Style = SynHighlighterVrml97__5;
	fEventAttri->Foreground = clNavy;
	fEventAttri->Background = clWhite;
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	fSpaceAttri->Style = SynHighlighterVrml97__6;
	fSpaceAttri->Foreground = clNavy;
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Style = SynHighlighterVrml97__7;
	fStringAttri->Foreground = clNavy;
	fStringAttri->Background = clWhite;
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	fSymbolAttri->Style = SynHighlighterVrml97__8;
	fSymbolAttri->Foreground = clNavy;
	fSymbolAttri->Background = clWhite;
	addAttribute(fSymbolAttri);
  //-- vrml
	fVrmlAppearanceAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlAppearance, SYNS_FriendlyAttrVrmlAppearance);
	fVrmlAppearanceAttri->Style = SynHighlighterVrml97__9;
	fVrmlAppearanceAttri->Foreground = clNavy;
	fVrmlAppearanceAttri->Background = clWhite;
	addAttribute(fVrmlAppearanceAttri);
	fVrmlAttributeAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlAttribute, SYNS_FriendlyAttrVrmlAttribute);
	fVrmlAttributeAttri->Style = SynHighlighterVrml97__10;
	fVrmlAttributeAttri->Foreground = clNavy;
	fVrmlAttributeAttri->Background = clGray;
	addAttribute(fVrmlAttributeAttri);
	fVrmlDefinitionAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlDefinition, SYNS_FriendlyAttrVrmlDefinition);
	fVrmlDefinitionAttri->Style = SynHighlighterVrml97__11;
	fVrmlDefinitionAttri->Foreground = clNavy;
	fVrmlDefinitionAttri->Background = clRed;
	addAttribute(fVrmlDefinitionAttri);
	fVrmlEventAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlEvent, SYNS_FriendlyAttrVrmlEvent);
	fVrmlEventAttri->Style = SynHighlighterVrml97__12;
	fVrmlEventAttri->Foreground = clRed;
	fVrmlEventAttri->Background = clWhite;
	addAttribute(fVrmlEventAttri);
	fVrmlGroupingAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlGrouping, SYNS_FriendlyAttrVrmlGrouping);
	fVrmlGroupingAttri->Style = SynHighlighterVrml97__13;
	fVrmlGroupingAttri->Foreground = clNavy;
	fVrmlGroupingAttri->Background = clWhite;
	addAttribute(fVrmlGroupingAttri);
	fVrmlInterpolatorAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlInterpolator, SYNS_FriendlyAttrVrmlInterpolator);
	fVrmlInterpolatorAttri->Style = SynHighlighterVrml97__14;
	fVrmlInterpolatorAttri->Foreground = clLime;
	fVrmlInterpolatorAttri->Background = clWhite;
	addAttribute(fVrmlInterpolatorAttri);
	fVrmlLightAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlLight, SYNS_FriendlyAttrVrmlLight);
	fVrmlLightAttri->Style = SynHighlighterVrml97__15;
	fVrmlLightAttri->Foreground = clTeal;
	fVrmlLightAttri->Background = clWhite;
	addAttribute(fVrmlLightAttri);
	fVrmlNodeAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlNode, SYNS_FriendlyAttrVrmlNode);
	fVrmlNodeAttri->Style = SynHighlighterVrml97__16;
	fVrmlNodeAttri->Foreground = clGreen;
	fVrmlNodeAttri->Background = clWhite;
	addAttribute(fVrmlNodeAttri);
	fVrmlParameterAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlParameter, SYNS_FriendlyAttrVrmlParameter);
	fVrmlParameterAttri->Style = SynHighlighterVrml97__17;
	fVrmlParameterAttri->Foreground = (TColor) 0xF0CAA6; //clSkyBlue
	fVrmlParameterAttri->Background = clWhite;
	addAttribute(fVrmlParameterAttri);
	fVrmlprotoAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlProto, SYNS_FriendlyAttrVrmlProto);
	fVrmlprotoAttri->Style = SynHighlighterVrml97__18;
	fVrmlprotoAttri->Foreground = clRed;
	fVrmlprotoAttri->Background = clWhite;
	addAttribute(fVrmlprotoAttri);
	fVrmlSensorAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlSensor, SYNS_FriendlyAttrVrmlSensor);
	fVrmlSensorAttri->Style = SynHighlighterVrml97__19;
	fVrmlSensorAttri->Foreground = clOlive;
	fVrmlSensorAttri->Background = clWhite;
	addAttribute(fVrmlSensorAttri);
	fVrmlShapeAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlShape, SYNS_FriendlyAttrVrmlShape);
	fVrmlShapeAttri->Style = SynHighlighterVrml97__20;
	fVrmlShapeAttri->Foreground = clPurple;
	fVrmlShapeAttri->Background = clWhite;
	addAttribute(fVrmlShapeAttri);
	fVrmlShape_HintAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlShape_Hint, SYNS_FriendlyAttrVrmlShape_Hint);
	fVrmlShape_HintAttri->Style = SynHighlighterVrml97__21;
	fVrmlShape_HintAttri->Foreground = clPurple;
	fVrmlShape_HintAttri->Background = clWhite;
	addAttribute(fVrmlShape_HintAttri);
	fVrmlTime_dependentAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlTime_dependent, SYNS_FriendlyAttrVrmlTime_dependent);
	fVrmlTime_dependentAttri->Style = SynHighlighterVrml97__22;
	fVrmlTime_dependentAttri->Foreground = clOlive;
	fVrmlTime_dependentAttri->Background = clWhite;
	addAttribute(fVrmlTime_dependentAttri);
	fVrmlViewpointAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlViewpoint, SYNS_FriendlyAttrVrmlViewpoint);
	fVrmlViewpointAttri->Style = SynHighlighterVrml97__23;
	fVrmlViewpointAttri->Foreground = clGreen;
	fVrmlViewpointAttri->Background = clWhite;
	addAttribute(fVrmlViewpointAttri);
	fVrmlWorldInfoAttri = new TSynHighlighterAttributes(SYNS_AttrVrmlWorldInfo, SYNS_FriendlyAttrVrmlWorldInfo);
	fVrmlWorldInfoAttri->Style = SynHighlighterVrml97__24;
	fVrmlWorldInfoAttri->Foreground = clMaroon;
	fVrmlWorldInfoAttri->Background = clWhite;
	addAttribute(fVrmlWorldInfoAttri);
	fX3DDocTypeAttri = new TSynHighlighterAttributes(SYNS_AttrX3DDocType, SYNS_FriendlyAttrX3DDocType);
	fX3DDocTypeAttri->Style = SynHighlighterVrml97__25;
	fX3DDocTypeAttri->Foreground = clMaroon;
	fX3DDocTypeAttri->Background = clWhite;
	addAttribute(fX3DDocTypeAttri);
	fX3DHeaderAttri = new TSynHighlighterAttributes(SYNS_AttrX3DHeader, SYNS_FriendlyAttrX3DHeader);
	fX3DHeaderAttri->Style = SynHighlighterVrml97__26;
	fX3DHeaderAttri->Foreground = clMaroon;
	fX3DHeaderAttri->Background = clWhite;
	addAttribute(fX3DHeaderAttri);
	SetAttributesOnChange(DefHighlightChange);
	EnumerateKeywords(int(tkEvent), Events, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkKey), Keywords, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkNonReservedKey), NonReservedKeys, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlAppearance), VrmlAppearances, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlAttribute), VrmlAttributes, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlDefinition), VrmlDefinitions, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlEvent), VrmlEvents, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlGrouping), VrmlGroupings, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlInterpolator), VrmlInterpolators, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlLight), VrmlLights, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlNode), VrmlNodes, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlParameter), VrmlParameters, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlproto), VrmlProtos, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlSensor), VrmlSensors, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlShape), VrmlShapes, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlShape_Hint), VrmlShape_Hints, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlTime_dependent), VrmlTime_dependents, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlViewpoint), VrmlViewpoints, IsIdentChar, DoAddKeyword);
	EnumerateKeywords(int(tkVrmlWorldInfo), VrmlWorldInfos, IsIdentChar, DoAddKeyword);
	fDefaultFilter = SYNS_FilterVrml97;
}

__fastcall TSynVrml97Syn::~TSynVrml97Syn()
{
	delete fKeywords;
	//# inherited::Destroy();
}


void __fastcall TSynVrml97Syn::AndSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], SynHighlighterVrml97__27))
		++Run;
}

bool __fastcall TSynVrml97Syn::NextTokenIs(String T)
{
	bool result = false;
	__int64 i = 0;
	int Len = 0;
	__int64 stop = 0;
	result = true;
	Len = (int) T.Length();
	for(stop = Len, i = 1; i <= stop; i++)
	{
		if(fLine[Run + i] != T[i])
		{
			result = false;
			break;
		}
	}
	return result;
}

void __fastcall TSynVrml97Syn::InCommentProc()
{
	if((fLine[Run + 1] == L'-') && (fLine[Run + 2] == L'-'))
	{
		++Run;
		FTokenID = tkComment;
		FRange = rsComment;
		Run += 2;
		do
		{
			++Run;
			if((fLine[Run] == L'-') && (fLine[Run + 1] == L'-'))
			{
				FRange = rsNormalText;
				Run += 2;
				break;
			}
		}
		while(!IsLineEnd(Run));
		return;
	}
}

void __fastcall TSynVrml97Syn::DiesisCommentProc()
{
	if(fLine[Run] == L'\x00')
		NullProc();
	else
	{
		FTokenID = tkComment;
		do
		{
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynVrml97Syn::X3DHeaderOpenProc()
{
	++Run;
	FRange = rsX3DHeader;
	X3DHeaderProc();
	FTokenID = tkX3DHeader;
}

void __fastcall TSynVrml97Syn::X3DHeaderProc()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		default:
		{
			FTokenID = tkX3DHeader;
			do
			{
				if(fLine[Run] == L'?')
				{
					Run += 1;
					FRange = rsNormalText;
					break;
				}
				if(!IsLineEnd(Run))
					++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynVrml97Syn::X3DDocTypeOpenProc()
{
	if(NextTokenIs(L"DOCTYPE"))
	{
		FRange = rsX3DDocType;
		X3DDocTypeProc();
		FTokenID = tkX3DDocType;
	}
	else
	{
		if(NextTokenIs(L"--"))
		{
			FRange = rsComment;
			InCommentProc();
			FTokenID = tkComment;
		}
		else
		{
			FTokenID = tkSymbol;
			++Run;
		}
	}
}

void __fastcall TSynVrml97Syn::X3DDocTypeProc()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		default:
		{
			FTokenID = tkX3DDocType;
			do
			{
				if(fLine[Run + 1] == L'>')
				{
					Run += 1;
					FRange = rsNormalText;
					break;
				}
				if(!IsLineEnd(Run))
					++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynVrml97Syn::CommentProc()
{
	if(fLine[Run] == L'\x00')
		NullProc();
	else
	{
		FTokenID = tkComment;
		do
		{
			if(((fLine[Run] == L'*') && (fLine[Run + 1] == L'/')) || ((fLine[Run] == L'-') && (fLine[Run + 1] == L'-')))
			{
				FRange = rsNormalText;
				Run += 2;
				break;
			}
			++Run;
		}
		while(!IsLineEnd(Run));
	}
}

void __fastcall TSynVrml97Syn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynVrml97Syn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynVrml97Syn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynVrml97Syn::MinusProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], SynHighlighterVrml97__28))
		++Run;
}

void __fastcall TSynVrml97Syn::ModSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynVrml97Syn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynVrml97Syn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'.':
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case L'x':
			case L'X':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	int idx1 = 0; // token[1]
	bool IsHex = false;
	FTokenID = tkNumber;
	IsHex = false;
	idx1 = Run;
	++Run;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Succ(Run)] == L'.')
				goto label0;
			break;
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			if(!IsHex)
				goto label1;
			break;
			case L'x':
			case L'X':
			{
				if((fLine[idx1] != L'0') || (Run > Succ(idx1)))
					goto label2;
				if(!CharInSet(fLine[Succ(Run)], SynHighlighterVrml97__29))
				{
					goto label3;
				}
				IsHex = true;
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
	label1:;
	label2:;
	label3:;
}

void __fastcall TSynVrml97Syn::OrSymbolProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], SynHighlighterVrml97__30))
		++Run;
}

void __fastcall TSynVrml97Syn::PlusProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(CharInSet(fLine[Run], SynHighlighterVrml97__31))
		++Run;
}

void __fastcall TSynVrml97Syn::PointProc()
{
	FTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'.') && (fLine[Run + 1] == L'.'))
		Run += 2;
}

void __fastcall TSynVrml97Syn::SlashProc()
{
	++Run;
	switch(fLine[Run])
	{
		case L'/':
		{
			FTokenID = tkComment;
			do
			{
				++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
		case L'*':
		{
			FTokenID = tkComment;
			FRange = rsComment;
			do
			{
				++Run;
				if((fLine[Run] == L'*') && (fLine[Run + 1] == L'/'))
				{
					FRange = rsNormalText;
					Run += 2;
					break;
				}
			}
			while(!IsLineEnd(Run));
		}
		break;
		case L'=':
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
		default:
		FTokenID = tkSymbol;
		break;
	}
}

void __fastcall TSynVrml97Syn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVrml97Syn::StarProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynVrml97Syn::StringProc()
{
	String l_strChar;
	FTokenID = tkString;
	l_strChar = fLine[Run]; // We could have '"' or #39
	if((fLine[Run + 1] == l_strChar) && (fLine[Run + 2] == l_strChar))
		Run += 2;
	do
	{
		if(IsLineEnd(Run))
			break;
		++Run;
	}
	while(!((fLine[Run] == l_strChar) && (fLine[Pred(Run)] != L'\\')));
	if(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynVrml97Syn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynVrml97Syn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynVrml97Syn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsX3DHeader:
		X3DHeaderProc();
		break;
		case rsX3DDocType:
		X3DDocTypeProc();
		break;
		case rsComment:
		CommentProc();
		break;
		default:
		switch(fLine[Run])
		{
			case L'&':
			AndSymbolProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L'#':
			DiesisCommentProc();
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			IdentProc();
			break;
			case L'\x0a':
			LFProc();
			break;
			case L'-':
			MinusProc();
			break;
			case L'%':
			ModSymbolProc();
			break;
			case L'\x00':
			NullProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
			break;
			case L'|':
			OrSymbolProc();
			break;
			case L'+':
			PlusProc();
			break;
			case L'.':
			PointProc();
			break;
			case L'/':
			SlashProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case L'*':
			StarProc();
			break;
			case L'\"':
			case L'\x27':
			StringProc();
			break;
			case L'?':
			X3DHeaderOpenProc();
			break;
			case L'!':
			X3DDocTypeOpenProc();
			break;
			case L'~':
			case L'{':
			case L'}':
			case L',':
			case L'(':
			case L')':
			case L'[':
			case L']':
			case L':':
			case L';':
			case L'=':
			case L'<':
			case L'>':
			SymbolProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynVrml97Syn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fKeyAttri;
		break;
		case SYN_ATTR_STRING:
		result = fStringAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		case SYN_ATTR_SYMBOL:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynVrml97Syn::GetEol()
{
	bool result = false;
	result = FTokenID == tkNull;
	return result;
}

void* __fastcall TSynVrml97Syn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

TtkTokenKind __fastcall TSynVrml97Syn::GetTokenID()
{
	TtkTokenKind result = tkComment;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynVrml97Syn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNonReservedKey:
		result = fNonReservedKeyAttri;
		break;
		case tkEvent:
		result = fEventAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
    // vrml
		case tkVrmlAppearance:
		result = fVrmlAppearanceAttri;
		break;
		case tkVrmlAttribute:
		result = fVrmlAttributeAttri;
		break;
		case tkVrmlDefinition:
		result = fVrmlDefinitionAttri;
		break;
		case tkVrmlEvent:
		result = fVrmlEventAttri;
		break;
		case tkVrmlGrouping:
		result = fVrmlGroupingAttri;
		break;
		case tkVrmlInterpolator:
		result = fVrmlInterpolatorAttri;
		break;
		case tkVrmlLight:
		result = fVrmlLightAttri;
		break;
		case tkVrmlNode:
		result = fVrmlNodeAttri;
		break;
		case tkVrmlParameter:
		result = fVrmlParameterAttri;
		break;
		case tkVrmlproto:
		result = fVrmlprotoAttri;
		break;
		case tkVrmlSensor:
		result = fVrmlSensorAttri;
		break;
		case tkVrmlShape:
		result = fVrmlShapeAttri;
		break;
		case tkVrmlShape_Hint:
		result = fVrmlShape_HintAttri;
		break;
		case tkVrmlTime_dependent:
		result = fVrmlTime_dependentAttri;
		break;
		case tkVrmlViewpoint:
		result = fVrmlViewpointAttri;
		break;
		case tkVrmlWorldInfo:
		result = fVrmlWorldInfoAttri;
		break;
		case tkX3DDocType:
		result = fX3DDocTypeAttri;
		break;
		case tkX3DHeader:
		result = fX3DHeaderAttri;
		break;
    //--
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynVrml97Syn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

void __fastcall TSynVrml97Syn::ResetRange()
{
	FRange = rsNormalText;
}

void __fastcall TSynVrml97Syn::SetRange(void* Value)
{
	FRange = (TRangeState)(int)Value;
}

bool __fastcall TSynVrml97Syn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterVrml97;
	return result;
}

/*#static*/
String __fastcall TSynVrml97Syn::GetLanguageName()
{
	String result;
	result = SYNS_LangVrml97;
	return result;
}

String __fastcall TSynVrml97Syn::GetSampleSource()
{
	String result;
	result = L"#VRML V2.0 utf8\x0d\x0a"
	           L"Transform {\x0d\x0a"
	           L"  children [\x0d\x0a"
	           L"    NavigationInfo { headlight FALSE } # We'll add our own light\x0d\x0a"
	           L"\x0d\x0a"
	           L"    DirectionalLight {        # First child\x0d\x0a"
	           L"        direction 0 0 -1      # Light illuminating the scene\x0d\x0a"
	           L"    }\x0d\x0a"
	           L"\x0d\x0a"
	           L"    Transform {               # Second child - a red sphere\x0d\x0a"
	           L"      translation 3 0 1\x0d\x0a"
	           L"      children [\x0d\x0a"
	           L"        Shape {\x0d\x0a"
	           L"          geometry Sphere { radius 2.3 }\x0d\x0a"
	           L"          appearance Appearance {\x0d\x0a"
	           L"            material Material { diffuseColor 1 0 0 }   # Red\x0d\x0a"
	           L"         }\x0d\x0a"
	           L"        }\x0d\x0a"
	           L"      ]\x0d\x0a"
	           L"    }\x0d\x0a"
	           L"\x0d\x0a"
	           L"    Transform {               # Third child - a blue box \x0d\x0a"
	           L"      translation -2.4 .2 1\x0d\x0a"
	           L"      rotation     0 1 1  .9\x0d\x0a"
	           L"      children [\x0d\x0a"
	           L"        Shape {\x0d\x0a"
	           L"          geometry Box {}\x0d\x0a"
	           L"          appearance Appearance {\x0d\x0a"
	           L"            material Material { diffuseColor 0 0 1 }  # Blue\x0d\x0a"
	           L"         }\x0d\x0a"
	           L"        }\x0d\x0a"
	           L"      ]\x0d\x0a"
	           L"    }\x0d\x0a"
	           L"\x0d\x0a"
	           L"  ] # end of children for world\x0d\x0a"
	           L"}\x0d\x0a"
	           L"DEF Example_2 Script {\x0d\x0a"
	           L"    field   SFNode myself USE Example_2\x0d\x0a"
	           L"    field   SFNode root USE ROOT_TRANSFORM\x0d\x0a"
	           L"    field   MFString url \"foo.wrl\"\x0d\x0a"
	           L"    eventIn MFNode   nodesLoaded\x0d\x0a"
	           L"    eventIn SFBool   trigger_event\x0d\x0a"
	           L"\x0d\x0a"
	           L"    url \"javascript:\x0d\x0a"
	           L"        function trigger_event(value, ts){\x0d\x0a"
	           L"            // do something and then fetch values\x0d\x0a"
	           L"            Browser.createVRMLFromURL(url, myself, 'nodesLoaded');\x0d\x0a"
	           L"        }\x0d\x0a"
	           L"\x0d\x0a"
	           L"        function nodesLoaded(value, timestamp){\x0d\x0a"
	           L"            if (value.length > 5) {\x0d\x0a"
	           L"                 // do something more than 5 nodes in this MFNode...\x0d\x0a"
	           L"            }\x0d\x0a"
	           L"            root.addChildren = value;\x0d\x0a"
	           L"        }\"\x0d\x0a"
	           L"}";
	return result;
}

/*#static*/
String __fastcall TSynVrml97Syn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangVrml97;
	return result;
}
static bool SynHighlighterVrml97_Initialized = false;

void SynHighlighterVrml97_initialization()
{
	if(SynHighlighterVrml97_Initialized)
		return;
	
	SynHighlighterVrml97_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynVrml97Syn));
}
class SynHighlighterVrml97_unit
{
public:
	SynHighlighterVrml97_unit()
	{
		SynHighlighterVrml97_initialization();
	}
};

SynHighlighterVrml97_unit _SynHighlighterVrml97_unit;

}  // namespace SynHighlighterVrml97

