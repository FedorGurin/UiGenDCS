// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fedor_msg.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "fedor_msg.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace fedor {
class SearhRequestDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<SearhRequest> {
} _SearhRequest_default_instance_;
class AnswerRequestDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<AnswerRequest> {
} _AnswerRequest_default_instance_;

namespace protobuf_fedor_5fmsg_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[2];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearhRequest, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearhRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearhRequest, name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearhRequest, id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SearhRequest, type_),
  0,
  1,
  2,
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AnswerRequest, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AnswerRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AnswerRequest, name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AnswerRequest, id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AnswerRequest, result_),
  0,
  1,
  2,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 7, sizeof(SearhRequest)},
  { 10, 17, sizeof(AnswerRequest)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_SearhRequest_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_AnswerRequest_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "fedor_msg.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

}  // namespace

void TableStruct::Shutdown() {
  _SearhRequest_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
  _AnswerRequest_default_instance_.Shutdown();
  delete file_level_metadata[1].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _SearhRequest_default_instance_.DefaultConstruct();
  _AnswerRequest_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\017fedor_msg.proto\022\005fedor\"\205\001\n\014SearhReques"
      "t\022\014\n\004name\030\001 \002(\t\022\n\n\002id\030\002 \002(\005\022,\n\004type\030\003 \002("
      "\0162\036.fedor.SearhRequest.TypePacket\"-\n\nTyp"
      "ePacket\022\017\n\013TEventStick\020\000\022\016\n\nTEventFobj\020\001"
      "\"9\n\rAnswerRequest\022\014\n\004name\030\001 \002(\t\022\n\n\002id\030\002 "
      "\002(\005\022\016\n\006result\030\003 \002(\005"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 219);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "fedor_msg.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_fedor_5fmsg_2eproto

const ::google::protobuf::EnumDescriptor* SearhRequest_TypePacket_descriptor() {
  protobuf_fedor_5fmsg_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_fedor_5fmsg_2eproto::file_level_enum_descriptors[0];
}
bool SearhRequest_TypePacket_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const SearhRequest_TypePacket SearhRequest::TEventStick;
const SearhRequest_TypePacket SearhRequest::TEventFobj;
const SearhRequest_TypePacket SearhRequest::TypePacket_MIN;
const SearhRequest_TypePacket SearhRequest::TypePacket_MAX;
const int SearhRequest::TypePacket_ARRAYSIZE;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SearhRequest::kNameFieldNumber;
const int SearhRequest::kIdFieldNumber;
const int SearhRequest::kTypeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SearhRequest::SearhRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_fedor_5fmsg_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:fedor.SearhRequest)
}
SearhRequest::SearhRequest(const SearhRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_name()) {
    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  ::memcpy(&id_, &from.id_,
    reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&id_) + sizeof(type_));
  // @@protoc_insertion_point(copy_constructor:fedor.SearhRequest)
}

void SearhRequest::SharedCtor() {
  _cached_size_ = 0;
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&id_, 0, reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&id_) + sizeof(type_));
}

SearhRequest::~SearhRequest() {
  // @@protoc_insertion_point(destructor:fedor.SearhRequest)
  SharedDtor();
}

void SearhRequest::SharedDtor() {
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void SearhRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SearhRequest::descriptor() {
  protobuf_fedor_5fmsg_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_fedor_5fmsg_2eproto::file_level_metadata[0].descriptor;
}

const SearhRequest& SearhRequest::default_instance() {
  protobuf_fedor_5fmsg_2eproto::InitDefaults();
  return *internal_default_instance();
}

SearhRequest* SearhRequest::New(::google::protobuf::Arena* arena) const {
  SearhRequest* n = new SearhRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void SearhRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:fedor.SearhRequest)
  if (has_name()) {
    GOOGLE_DCHECK(!name_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
    (*name_.UnsafeRawStringPointer())->clear();
  }
  if (_has_bits_[0 / 32] & 6u) {
    ::memset(&id_, 0, reinterpret_cast<char*>(&type_) -
      reinterpret_cast<char*>(&id_) + sizeof(type_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool SearhRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:fedor.SearhRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (tag == 10u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "fedor.SearhRequest.name");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 id = 2;
      case 2: {
        if (tag == 16u) {
          set_has_id();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .fedor.SearhRequest.TypePacket type = 3;
      case 3: {
        if (tag == 24u) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::fedor::SearhRequest_TypePacket_IsValid(value)) {
            set_type(static_cast< ::fedor::SearhRequest_TypePacket >(value));
          } else {
            mutable_unknown_fields()->AddVarint(3, value);
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:fedor.SearhRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:fedor.SearhRequest)
  return false;
#undef DO_
}

void SearhRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:fedor.SearhRequest)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "fedor.SearhRequest.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // required int32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->id(), output);
  }

  // required .fedor.SearhRequest.TypePacket type = 3;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->type(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:fedor.SearhRequest)
}

::google::protobuf::uint8* SearhRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:fedor.SearhRequest)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "fedor.SearhRequest.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // required int32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->id(), target);
  }

  // required .fedor.SearhRequest.TypePacket type = 3;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->type(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:fedor.SearhRequest)
  return target;
}

size_t SearhRequest::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:fedor.SearhRequest)
  size_t total_size = 0;

  if (has_name()) {
    // required string name = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  if (has_id()) {
    // required int32 id = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->id());
  }

  if (has_type()) {
    // required .fedor.SearhRequest.TypePacket type = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
  }

  return total_size;
}
size_t SearhRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:fedor.SearhRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required string name = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());

    // required int32 id = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->id());

    // required .fedor.SearhRequest.TypePacket type = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SearhRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:fedor.SearhRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const SearhRequest* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SearhRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:fedor.SearhRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:fedor.SearhRequest)
    MergeFrom(*source);
  }
}

void SearhRequest::MergeFrom(const SearhRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:fedor.SearhRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 7u) {
    if (from.has_name()) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
}

void SearhRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:fedor.SearhRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SearhRequest::CopyFrom(const SearhRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:fedor.SearhRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SearhRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  return true;
}

void SearhRequest::Swap(SearhRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SearhRequest::InternalSwap(SearhRequest* other) {
  name_.Swap(&other->name_);
  std::swap(id_, other->id_);
  std::swap(type_, other->type_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata SearhRequest::GetMetadata() const {
  protobuf_fedor_5fmsg_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_fedor_5fmsg_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// SearhRequest

// required string name = 1;
bool SearhRequest::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void SearhRequest::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
void SearhRequest::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
void SearhRequest::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
const ::std::string& SearhRequest::name() const {
  // @@protoc_insertion_point(field_get:fedor.SearhRequest.name)
  return name_.GetNoArena();
}
void SearhRequest::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:fedor.SearhRequest.name)
}
#if LANG_CXX11
void SearhRequest::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:fedor.SearhRequest.name)
}
#endif
void SearhRequest::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:fedor.SearhRequest.name)
}
void SearhRequest::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:fedor.SearhRequest.name)
}
::std::string* SearhRequest::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:fedor.SearhRequest.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* SearhRequest::release_name() {
  // @@protoc_insertion_point(field_release:fedor.SearhRequest.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void SearhRequest::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:fedor.SearhRequest.name)
}

// required int32 id = 2;
bool SearhRequest::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void SearhRequest::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
void SearhRequest::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
void SearhRequest::clear_id() {
  id_ = 0;
  clear_has_id();
}
::google::protobuf::int32 SearhRequest::id() const {
  // @@protoc_insertion_point(field_get:fedor.SearhRequest.id)
  return id_;
}
void SearhRequest::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:fedor.SearhRequest.id)
}

// required .fedor.SearhRequest.TypePacket type = 3;
bool SearhRequest::has_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void SearhRequest::set_has_type() {
  _has_bits_[0] |= 0x00000004u;
}
void SearhRequest::clear_has_type() {
  _has_bits_[0] &= ~0x00000004u;
}
void SearhRequest::clear_type() {
  type_ = 0;
  clear_has_type();
}
::fedor::SearhRequest_TypePacket SearhRequest::type() const {
  // @@protoc_insertion_point(field_get:fedor.SearhRequest.type)
  return static_cast< ::fedor::SearhRequest_TypePacket >(type_);
}
void SearhRequest::set_type(::fedor::SearhRequest_TypePacket value) {
  assert(::fedor::SearhRequest_TypePacket_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:fedor.SearhRequest.type)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int AnswerRequest::kNameFieldNumber;
const int AnswerRequest::kIdFieldNumber;
const int AnswerRequest::kResultFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

AnswerRequest::AnswerRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_fedor_5fmsg_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:fedor.AnswerRequest)
}
AnswerRequest::AnswerRequest(const AnswerRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_name()) {
    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  ::memcpy(&id_, &from.id_,
    reinterpret_cast<char*>(&result_) -
    reinterpret_cast<char*>(&id_) + sizeof(result_));
  // @@protoc_insertion_point(copy_constructor:fedor.AnswerRequest)
}

void AnswerRequest::SharedCtor() {
  _cached_size_ = 0;
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&id_, 0, reinterpret_cast<char*>(&result_) -
    reinterpret_cast<char*>(&id_) + sizeof(result_));
}

AnswerRequest::~AnswerRequest() {
  // @@protoc_insertion_point(destructor:fedor.AnswerRequest)
  SharedDtor();
}

void AnswerRequest::SharedDtor() {
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void AnswerRequest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AnswerRequest::descriptor() {
  protobuf_fedor_5fmsg_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_fedor_5fmsg_2eproto::file_level_metadata[1].descriptor;
}

const AnswerRequest& AnswerRequest::default_instance() {
  protobuf_fedor_5fmsg_2eproto::InitDefaults();
  return *internal_default_instance();
}

AnswerRequest* AnswerRequest::New(::google::protobuf::Arena* arena) const {
  AnswerRequest* n = new AnswerRequest;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void AnswerRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:fedor.AnswerRequest)
  if (has_name()) {
    GOOGLE_DCHECK(!name_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
    (*name_.UnsafeRawStringPointer())->clear();
  }
  if (_has_bits_[0 / 32] & 6u) {
    ::memset(&id_, 0, reinterpret_cast<char*>(&result_) -
      reinterpret_cast<char*>(&id_) + sizeof(result_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool AnswerRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:fedor.AnswerRequest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (tag == 10u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "fedor.AnswerRequest.name");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 id = 2;
      case 2: {
        if (tag == 16u) {
          set_has_id();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 result = 3;
      case 3: {
        if (tag == 24u) {
          set_has_result();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &result_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:fedor.AnswerRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:fedor.AnswerRequest)
  return false;
#undef DO_
}

void AnswerRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:fedor.AnswerRequest)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "fedor.AnswerRequest.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // required int32 id = 2;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->id(), output);
  }

  // required int32 result = 3;
  if (has_result()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->result(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:fedor.AnswerRequest)
}

::google::protobuf::uint8* AnswerRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:fedor.AnswerRequest)
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "fedor.AnswerRequest.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // required int32 id = 2;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->id(), target);
  }

  // required int32 result = 3;
  if (has_result()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->result(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:fedor.AnswerRequest)
  return target;
}

size_t AnswerRequest::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:fedor.AnswerRequest)
  size_t total_size = 0;

  if (has_name()) {
    // required string name = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  if (has_id()) {
    // required int32 id = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->id());
  }

  if (has_result()) {
    // required int32 result = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->result());
  }

  return total_size;
}
size_t AnswerRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:fedor.AnswerRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required string name = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());

    // required int32 id = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->id());

    // required int32 result = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->result());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AnswerRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:fedor.AnswerRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const AnswerRequest* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const AnswerRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:fedor.AnswerRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:fedor.AnswerRequest)
    MergeFrom(*source);
  }
}

void AnswerRequest::MergeFrom(const AnswerRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:fedor.AnswerRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 7u) {
    if (from.has_name()) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_result()) {
      set_result(from.result());
    }
  }
}

void AnswerRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:fedor.AnswerRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AnswerRequest::CopyFrom(const AnswerRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:fedor.AnswerRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AnswerRequest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  return true;
}

void AnswerRequest::Swap(AnswerRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void AnswerRequest::InternalSwap(AnswerRequest* other) {
  name_.Swap(&other->name_);
  std::swap(id_, other->id_);
  std::swap(result_, other->result_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata AnswerRequest::GetMetadata() const {
  protobuf_fedor_5fmsg_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_fedor_5fmsg_2eproto::file_level_metadata[1];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// AnswerRequest

// required string name = 1;
bool AnswerRequest::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void AnswerRequest::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
void AnswerRequest::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
void AnswerRequest::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
const ::std::string& AnswerRequest::name() const {
  // @@protoc_insertion_point(field_get:fedor.AnswerRequest.name)
  return name_.GetNoArena();
}
void AnswerRequest::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:fedor.AnswerRequest.name)
}
#if LANG_CXX11
void AnswerRequest::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:fedor.AnswerRequest.name)
}
#endif
void AnswerRequest::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:fedor.AnswerRequest.name)
}
void AnswerRequest::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:fedor.AnswerRequest.name)
}
::std::string* AnswerRequest::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:fedor.AnswerRequest.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* AnswerRequest::release_name() {
  // @@protoc_insertion_point(field_release:fedor.AnswerRequest.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void AnswerRequest::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:fedor.AnswerRequest.name)
}

// required int32 id = 2;
bool AnswerRequest::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void AnswerRequest::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
void AnswerRequest::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
void AnswerRequest::clear_id() {
  id_ = 0;
  clear_has_id();
}
::google::protobuf::int32 AnswerRequest::id() const {
  // @@protoc_insertion_point(field_get:fedor.AnswerRequest.id)
  return id_;
}
void AnswerRequest::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:fedor.AnswerRequest.id)
}

// required int32 result = 3;
bool AnswerRequest::has_result() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void AnswerRequest::set_has_result() {
  _has_bits_[0] |= 0x00000004u;
}
void AnswerRequest::clear_has_result() {
  _has_bits_[0] &= ~0x00000004u;
}
void AnswerRequest::clear_result() {
  result_ = 0;
  clear_has_result();
}
::google::protobuf::int32 AnswerRequest::result() const {
  // @@protoc_insertion_point(field_get:fedor.AnswerRequest.result)
  return result_;
}
void AnswerRequest::set_result(::google::protobuf::int32 value) {
  set_has_result();
  result_ = value;
  // @@protoc_insertion_point(field_set:fedor.AnswerRequest.result)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace fedor

// @@protoc_insertion_point(global_scope)
