# QML Rest

## Sample usage

###  Simple get request

```json
WebRequest  {
  id:  service
  url:  "http://httpbin.org/get"

  response:  JsonResponse  {
	  onFinished:  console.log(JSON.stringify(data))
  }
}
```

### Post data
```json
WebRequest  {
  id:  service
  url:  "http://httpbin.org/post"
  loadingText:  "Posting  data"
  data:  JsonPostData  {
	  data:  ({
		  name:  'hamed',
		  n:  1
	  })
  }

  response:  JsonResponse  {
	  onFinished:  console.log(JSON.stringify(data))
	  onError:  console.log("error",  descript)
  }
}
```

## Types of data

### FormPostData
More document will be written soon!

### JsonPostData
More document will be written soon!

### FilePostData
More document will be written soon!

### RawBody
More document will be written soon!

### QueryString
More document will be written soon!

## Response types

### StringResponse
More document will be written soon!

### JsonResponse
More document will be written soon!

### ImageResponse
More document will be written soon!