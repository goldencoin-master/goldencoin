// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa3;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xd0;
        pchMessageStart[3] = 0xb8;
        vAlertPubKey = ParseHex("04e432194493ec53f227bde0d51c37929b2d6e128ab10c267ad0003b31516db22626fa76c7e815b0ddebfc3e89d4d6a4a0086aa9c73081dcf68d3d4c2c4275d227");
        nDefaultPort = 12881;
        nRPCPort = 2881;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
//        genesis.nTime = 1631055015
//        genesis.nNonce = 579674
//        genesis.nVersion = 1
//        genesis.GetHash = d79e8d3dd98f145a9c61d134b44350a6898980162a11d29f24f09208e3a688da
//        genesis.hashMerkleRoot = 1481397caf139d6ea984b111d8ff448783353b9d82bb3a15254bbb223e19c63d

        const char* pszTimestamp = "Forkast.News 09/7/2021: El Salvador today becomes first country to adopt Bitcoin as legal tender";
        CTransaction txNew;
        txNew.nTime = 1631055015;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1631055015;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1048577;
// uncomment to log genesis block info        
//      //  start
/*        if (true && genesis.GetHash() != hashGenesisBlock)
                       {
                          printf("Searching for genesis block...\n");
                           uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                           uint256 thash;

                           while (true)
                           {
                               thash = genesis.GetHash();
                               if (thash <= hashTarget)
                                   break;
                               if ((genesis.nNonce & 0xFFF) == 0)
                               {
                                   printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                               }
                               ++genesis.nNonce;
                               if (genesis.nNonce == 0)
                               {
                                   printf("NONCE WRAPPED, incrementing time\n");
                                   ++genesis.nTime;
                               }
                           }
                           printf("genesis.nTime = %u \n", genesis.nTime);
                           printf("genesis.nNonce = %u \n", genesis.nNonce);
                           printf("genesis.nVersion = %u \n", genesis.nVersion);
                           printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
                           printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root

                       }

//        //end*/
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0f7f3963093e3a797d66ed2375cf6e0e8f18b0b9131e89124c887256f418d8bd"));
        assert(genesis.hashMerkleRoot == uint256("0xcb8f97dc44a68e1bfcc9c9bf7d0f5d44c810884126449a2bac27f34aca94d3ab"));

        vSeeds.push_back(CDNSSeedData("144.202.107.174", "144.202.107.174"));
        

        base58Prefixes[PUBKEY_ADDRESS] = list_of(38).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(97).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY] =     list_of(171).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
//genesis.nTime = 1495135892
//        genesis.nNonce = 207039
//        genesis.nVersion = 1
//        genesis.hashMerkleRoot = 82088963398534e82c649f9069c5f79bfcd9744cb4c6a8fc5e5f5080b6a9d777
//        genesis.GetHash = 00002a22a9993977bc613c110e298131d808ae2923e42714547841e5b8bd436b

        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xf6;
        pchMessageStart[2] = 0xd2;
        pchMessageStart[3] = 0xa1;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04e432194493ec53f227bde0d51c37929b2d6e128ab10c267ad0003b31516db22626fa76c7e815b0ddebfc3e89d4d6a4a0086aa9c73081dcf68d3d4c2c4275d227");
        nDefaultPort = 22881;
        nRPCPort = 22881;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 207039;
//uncomment to log genesis block info
//          
/*          if (true && genesis.GetHash() != hashGenesisBlock)
                         {
                             printf("Searching for genesis block...\n");
                             uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                             uint256 thash;

                             while (true)
                             {
                                 thash = genesis.GetHash();
                                 if (thash <= hashTarget)
                                     break;
                                 if ((genesis.nNonce & 0xFFF) == 0)
                                 {
                                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                                 }
                                 ++genesis.nNonce;
                                 if (genesis.nNonce == 0)
                                 {
                                     printf("NONCE WRAPPED, incrementing time\n");
                                     ++genesis.nTime;
                                }
                             }
                             printf("genesis.nTime = %u \n", genesis.nTime);
                             printf("genesis.nNonce = %u \n", genesis.nNonce);
                             printf("genesis.nVersion = %u \n", genesis.nVersion);
                             printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
                             printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());

                         }

//*/
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xbbed331228979c3d8c756e9462b531ec2042683eb7f05cd06ffaa6a4f16c1275"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(65).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(127).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(239).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
//genesis.nTime = 1495135892
//genesis.nNonce = 2
//genesis.nVersion = 1
//genesis.hashMerkleRoot = 82088963398534e82c649f9069c5f79bfcd9744cb4c6a8fc5e5f5080b6a9d777
//genesis.GetHash = 1a41c211ca6effbc731c344ab0288409541cb0ba716690a80bfce91fbdb89dfb

class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xf2;
        pchMessageStart[1] = 0xa0;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xc0;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1631055015;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 10444;
        strDataDir = "regtest";
//uncomment to log regtest genesis block info
//                 
/*        if (true)
                         {
                             printf("Searching for genesis block...\n");
                             uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
                             uint256 thash;

                             while (true)
                             {
                                 thash = genesis.GetHash();
                                 if (thash <= hashTarget)
                                     break;
                                 if ((genesis.nNonce & 0xFFF) == 0)
                                 {
                                     printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                                 }
                                 ++genesis.nNonce;
                                 if (genesis.nNonce == 0)
                                 {
                                     printf("NONCE WRAPPED, incrementing time\n");
                                     ++genesis.nTime;
                                 }
                             }
                             printf("genesis.nTime = %u \n", genesis.nTime);
                             printf("genesis.nNonce = %u \n", genesis.nNonce);
                             printf("genesis.nVersion = %u \n", genesis.nVersion);
                             printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //idk
                             printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());

                         }

//*/
        assert(hashGenesisBlock == uint256("0x2bf15d8844da9e98b78bb4396ef92027b5ce10d0bf72822e55bcdd350148c741"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
