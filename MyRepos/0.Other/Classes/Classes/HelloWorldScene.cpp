#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);


	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("aaa.png");
	
	
//	Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey("aaa.png");

    
    return true;
}
 
#if 0


// 将图片解压缩
bool Image::initWithImageFile(const std::string& path)
{
	bool ret = false;
	_filePath = FileUtils::getInstance()->fullPathForFilename(path);

#ifdef EMSCRIPTEN
	// Emscripten includes a re-implementation of SDL that uses HTML5 canvas
	// operations underneath. Consequently, loading images via IMG_Load (an SDL
	// API) will be a lot faster than running libpng et al as compiled with
	// Emscripten.
	SDL_Surface *iSurf = IMG_Load(fullPath.c_str());

	int size = 4 * (iSurf->w * iSurf->h);
	ret = initWithRawData((const unsigned char*)iSurf->pixels, size, iSurf->w, iSurf->h, 8, true);

	unsigned int *tmp = (unsigned int *)_data;
	int nrPixels = iSurf->w * iSurf->h;
	for (int i = 0; i < nrPixels; i++)
	{
		unsigned char *p = _data + i * 4;
		tmp[i] = CC_RGB_PREMULTIPLY_ALPHA(p[0], p[1], p[2], p[3]);
	}

	SDL_FreeSurface(iSurf);
#else
	// FileUtils是文件操作工具类
	Data data = FileUtils::getInstance()->getDataFromFile(_filePath);

	if (!data.isNull())
	{
		ret = initWithImageData(data.getBytes(), data.getSize());
	}
#endif // EMSCRIPTEN

	return ret;
}

// 通过data数据（压缩的图片数据），解压缩原始图片文件
bool Image::initWithImageData(const unsigned char * data, ssize_t dataLen)
{
	bool ret = false;

	do
	{
		CC_BREAK_IF(!data || dataLen <= 0);


		// 解压缩数据，指的是图片格式文件又经过了zip之类的压缩情况
		unsigned char* unpackedData = nullptr;
		ssize_t unpackedLen = 0;

		//detect and unzip the compress file
		if (ZipUtils::isCCZBuffer(data, dataLen))
		{
			unpackedLen = ZipUtils::inflateCCZBuffer(data, dataLen, &unpackedData);
		}
		else if (ZipUtils::isGZipBuffer(data, dataLen))
		{
			unpackedLen = ZipUtils::inflateMemory(const_cast<unsigned char*>(data), dataLen, &unpackedData);
		}
		else
		{
			unpackedData = const_cast<unsigned char*>(data);
			unpackedLen = dataLen;
		}

		// 图片数据已经在unpackedData中
		// 通过数据检测文件格式
		_fileType = detectFormat(unpackedData, unpackedLen);

		// 根据文件格式，将压缩图片文件，解压缩成原始图片格式文件
		switch (_fileType)
		{
		case Format::PNG:
			ret = initWithPngData(unpackedData, unpackedLen);
			break;
		case Format::JPG:
			ret = initWithJpgData(unpackedData, unpackedLen);
			break;
		case Format::TIFF:
			ret = initWithTiffData(unpackedData, unpackedLen);
			break;
		case Format::WEBP:
			ret = initWithWebpData(unpackedData, unpackedLen);
			break;
		case Format::PVR:
			ret = initWithPVRData(unpackedData, unpackedLen);
			break;
		case Format::ETC:
			ret = initWithETCData(unpackedData, unpackedLen);
			break;
		case Format::S3TC:
			ret = initWithS3TCData(unpackedData, unpackedLen);
			break;
		case Format::ATITC:
			ret = initWithATITCData(unpackedData, unpackedLen);
			break;
		default:
		{
				   // load and detect image format
				   tImageTGA* tgaData = tgaLoadBuffer(unpackedData, unpackedLen);

				   if (tgaData != nullptr && tgaData->status == TGA_OK)
				   {
					   ret = initWithTGAData(tgaData);
				   }
				   else
				   {
					   CCAssert(false, "unsupport image format!");
				   }

				   free(tgaData);
				   break;
		}
		}

		if (unpackedData != data)
		{
			free(unpackedData);
		}
	} while (0);

	return ret;
}


// implementation Texture2D (Image)
bool Texture2D::initWithImage(Image *image)
{
	return initWithImage(image, g_defaultAlphaPixelFormat);
}

Texture2D * TextureCache::addImage(const std::string &path)
{
	Texture2D * texture = nullptr;
	Image* image = nullptr;
	// Split up directory and filename
	// MUTEX:
	// Needed since addImageAsync calls this method from a different thread

	// 把path对应的全路径获取
	std::string fullpath = FileUtils::getInstance()->fullPathForFilename(path);
	if (fullpath.size() == 0)
	{
		return nullptr;
	}

	// 在纹理集合里查找纹理
	// _textures就是保存纹理混存的那个集合
	auto it = _textures.find(fullpath);
	// 找到了
	if (it != _textures.end())
		texture = it->second;

	// 如果没有找到纹理，那么要通过文件路径，去创建一个纹理，并且放入纹理缓存
	if (!texture)
	{
		// all images are handled by UIImage except PVR extension that is handled by our own handler
		do
		{
			// 创建一个Image对象
			image = new (std::nothrow) Image();
			CC_BREAK_IF(nullptr == image);

			// 初始化Image对象，通过图片文件初始化Image
			bool bRet = image->initWithImageFile(fullpath);
			CC_BREAK_IF(!bRet);

			// 创建纹理
			texture = new (std::nothrow) Texture2D();

			// 通过Image对象初始化纹理
			if (texture && texture->initWithImage(image))
			{
#if CC_ENABLE_CACHE_TEXTURE_DATA
				// cache the texture file name
				VolatileTextureMgr::addImageTexture(texture, fullpath);
#endif
				// 把纹理放入容器
				// texture already retained, no need to re-retain it
				_textures.insert(std::make_pair(fullpath, texture));
			}
			else
			{
				CCLOG("cocos2d: Couldn't create texture for file:%s in TextureCache", path.c_str());
			}
		} while (0);
	}

	// 如果image是new出来的内容，那么调用release
	CC_SAFE_RELEASE(image);

	// 返回纹理
	return texture;
}
#endif

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
