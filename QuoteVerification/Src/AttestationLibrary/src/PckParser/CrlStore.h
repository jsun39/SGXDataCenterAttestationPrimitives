/*
* Copyright (c) 2017-2018, Intel Corporation
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:

* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef SGX_INTEL_QVL_CRLSTORE_H_
#define SGX_INTEL_QVL_CRLSTORE_H_

#include "PckParser.h"
#include "CertStore.h"

#include <OpensslHelpers/OpensslTypes.h>

namespace intel { namespace sgx { namespace qvl { namespace pckparser {

class CrlStore
{
public:
    CrlStore();
    CrlStore(const CrlStore&) = delete;
    CrlStore(CrlStore&&) = default;
    virtual ~CrlStore() = default;

    CrlStore& operator=(const CrlStore&) = delete;
    CrlStore& operator=(CrlStore&&) = default;
    bool operator==(const CrlStore& other) const;
    bool operator!=(const CrlStore& other) const;

    virtual bool parse(const std::string& pemCrl);

    virtual bool expired() const;
    virtual const Issuer& getIssuer() const;
    virtual const Validity& getValidity() const;
    virtual const Signature& getSignature() const;
    virtual const std::vector<Extension>& getExtensions() const;
    virtual const std::vector<Revoked>& getRevoked() const;
    virtual const X509_CRL& getCrl() const;
    virtual bool isRevoked(const CertStore& cert) const;

private:
    crypto::X509_CRL_uptr _crl;

    Issuer _issuer;
    Validity _validity;
    std::vector<Revoked> _revoked;
    std::vector<Extension> _extensions;
    Signature _signature;
};

}}}} // namespace intel { namespace sgx { namespace qvl { namespace pckparser {

#endif // SGX_INTEL_QVL_CRLSTORE_H_
